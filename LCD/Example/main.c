#include "LCD.h"

int main(){
		 myLCD.PORT_DATA = GPIOA;
		 myLCD.PORT_CMD  = GPIOB;
		 myLCD.D0 = GPIO_Pin_0;
		 myLCD.D1 = GPIO_Pin_1;
		 myLCD.D2 = GPIO_Pin_2;
		 myLCD.D3 = GPIO_Pin_3;
		 myLCD.D4 = GPIO_Pin_4;
		 myLCD.D5 = GPIO_Pin_5;
		 myLCD.D6 = GPIO_Pin_6;
		 myLCD.D7 = GPIO_Pin_7;
		 myLCD.RS = GPIO_Pin_0;
		 myLCD.RW = GPIO_Pin_1;
		 myLCD.E  = GPIO_Pin_10;
		
		LCD_Init();
		//LCD_Write_data('A');
		//LCD_String("Hai Yen Cute");
		LCD_String_XY(0, 0, "Hai");
		LCD_String_XY(1, 4, "Yen");
		Delay_ms(1000);
		LCD_clear();
		LCD_number(1300);
		LCD_Number_XY(1,4,1105);
		while(1){
		}
}

