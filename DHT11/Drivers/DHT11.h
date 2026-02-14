#ifndef __DHT11_H
#define __DHT11_H

#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include"stm32f10x_rcc.h"
#include"stm32f10x_tim.h"
#define DHT_PORT GPIOA 
#define DHT_PIN GPIO_Pin_2

void GPIO_configure(uint8_t mode); 
void Timer2_Register(void); 
void Delay_ms(uint32_t ms); 
void Delay_us(uint32_t us); 
uint8_t DHT11_Start(); 
uint8_t DHT_read_byte(); 
void DHT11_program();

#endif