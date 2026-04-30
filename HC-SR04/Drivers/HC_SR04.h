#ifndef HC_SR04_H
#define HC_SR04_H

#include"stm32f10x.h"
#include"stm32f10x_gpio.h"
#include"stm32f10x_rcc.h"
#include"stm32f10x_adc.h"
#include"stm32f10x_dma.h"
#include"stm32f10x_tim.h"

#define TRIG_Pin GPIO_Pin_1
#define ECHO_Pin GPIO_Pin_0

void HC_SR04Init(void);
void HC_SR04_TRIG(void);
uint32_t HC_SR04_ECHO(void);
float Get_Distance(void);
void Delay_Systick_Init(uint32_t clk);
void Delay_Systick_US(uint32_t time_us);
void Delay_Systick_MS(uint32_t time_ms);

#endif 