#ifndef LCD_H
#define LCD_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/*
RS & RW: PORT_CMD
D0 - D7: PORT_DATA
*/

typedef struct{
		GPIO_TypeDef *PORT_DATA;
		GPIO_TypeDef *PORT_CMD;
		uint16_t D0;
		uint16_t D1;
		uint16_t D2;
		uint16_t D3;
		uint16_t D4;
		uint16_t D5;
		uint16_t D6;
		uint16_t D7;
		uint16_t RS;
		uint16_t RW;
		uint16_t E;
}LCD;

extern LCD myLCD;


#define LCD_data 0x01
#define LCD_cmd  0x00

void Delay_ms(uint16_t time);
void GPIO_configure(void);
void LCD_Init(void);
void LCD_clear(void);
void LCD_Write_Byte(uint8_t data,uint8_t mode);
void LCD_Write_data(uint8_t data);
void LCD_Write_cmd(uint8_t data);
void LCD_String (char *str);
void LCD_String_XY(uint8_t row, uint8_t col, char *str);
void LCD_number(uint32_t number);
void LCD_Number_XY(uint8_t row, uint8_t col, uint32_t number);
#endif