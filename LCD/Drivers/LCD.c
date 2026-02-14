#include "LCD.h"

LCD myLCD;

void GPIO_configure(void){
    GPIO_InitTypeDef GPIO_InitStruct;

    /* Enable clock cho PORT_DATA */
    if (myLCD.PORT_DATA == GPIOA)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    else if (myLCD.PORT_DATA == GPIOB)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    else if (myLCD.PORT_DATA == GPIOC)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* Enable clock cho PORT_CMD */
    if (myLCD.PORT_CMD != myLCD.PORT_DATA){
        if (myLCD.PORT_CMD == GPIOA)
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        else if (myLCD.PORT_CMD == GPIOB)
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        else if (myLCD.PORT_CMD == GPIOC)
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    }

    /* DATA pins */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Pin =
        myLCD.D0 | myLCD.D1 | myLCD.D2 | myLCD.D3 |
        myLCD.D4 | myLCD.D5 | myLCD.D6 | myLCD.D7;

    GPIO_Init(myLCD.PORT_DATA, &GPIO_InitStruct);

    /* CONTROL pins */
    GPIO_InitStruct.GPIO_Pin =
        myLCD.RS | myLCD.RW | myLCD.E;

    GPIO_Init(myLCD.PORT_CMD, &GPIO_InitStruct);
}


void Delay_ms(uint16_t time){ //ham delay
		volatile uint16_t i,j;
		for(i = 0; i < time; i++){
			for(j = 0; j < 0x2AFF; j++);
	}
}

void LCD_Write_Byte(uint8_t data,uint8_t mode){  
		if(mode == LCD_data){
			GPIO_WriteBit(myLCD.PORT_CMD, myLCD.RS, 1); //RS = 1
		}else if(mode == LCD_cmd){
			GPIO_WriteBit(myLCD.PORT_CMD, myLCD.RS, 0); //RS = 0
		}
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D0, (data & 0x01) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D1, (data & 0x02) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D2, (data & 0x04) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D3, (data & 0x08) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D4, (data & 0x10) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D5, (data & 0x20) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D6, (data & 0x40) ? 1 : 0);
		GPIO_WriteBit(myLCD.PORT_DATA, myLCD.D7, (data & 0x80) ? 1 : 0);
		
		GPIO_WriteBit(myLCD.PORT_CMD, myLCD.E, 0);
		Delay_ms(1);
		GPIO_WriteBit(myLCD.PORT_CMD, myLCD.E, 1);
		Delay_ms(1);
		GPIO_WriteBit(myLCD.PORT_CMD, myLCD.E, 0);
		Delay_ms(1);
}

void LCD_Write_data(uint8_t data){ //data
		LCD_Write_Byte(data,1);
}
void LCD_Write_cmd(uint8_t data){ //cmd
		LCD_Write_Byte(data,0);
}

void LCD_Init(void){ // khoi tao
		GPIO_configure();
		GPIO_WriteBit(myLCD.PORT_CMD,myLCD.RW,0);
		Delay_ms(50);
		LCD_Write_cmd(0x38);
		Delay_ms(5);
		LCD_Write_cmd(0x0C);
		Delay_ms(5);
		LCD_Write_cmd(0x01); 
    Delay_ms(5);
		LCD_Write_cmd(0x06);
		Delay_ms(5);
}

void LCD_String(char *str){ // chuoi 
	while(*str){
			LCD_Write_data(*str++);
	}
}

void LCD_String_XY(uint8_t row, uint8_t col, char *str){
    uint8_t address;
    if(col >= 16) return;   
    if(row == 0){
        address = 0x00 + col;
    }
    else if(row == 1){
        address = 0x40 + col;
    }
    else{
        return;           
    }

    LCD_Write_cmd(0x80 | address);  
    LCD_String(str);         
}

void LCD_number(uint32_t number){
		if(number < 10){
			LCD_Write_data(number + 0x30);
		}else{
			uint32_t cnt = 0;
			char buff[100];
			while(number > 0){
				uint32_t tmp = number % 10;
				buff[cnt++] = tmp; 
				//LCD_Write_data(tmp + 0x30);
				number /= 10;
			}
			while(cnt > 0){
				LCD_Write_data(buff[--cnt] + 0x30);
		}
	}
}

void LCD_Number_XY(uint8_t row, uint8_t col, uint32_t number){
    uint8_t address;
    if(col >= 16) return;   
    if(row == 0){
        address = 0x00 + col;
    }
    else if(row == 1){
        address = 0x40 + col;
    }
    else{
        return;           
    }

    LCD_Write_cmd(0x80 | address);  
    LCD_number(number);        
}

void LCD_clear(void){
		LCD_Write_cmd(0x01);
}
