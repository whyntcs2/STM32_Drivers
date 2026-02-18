#ifndef Light_Sensor_H
#define Light_Sensor_H


#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define ADC1_DR_ADDRESS	((uint32_t)0x4001244C) 

void Delay_ms(uint32_t time);
void ADC_config(void);
void GPIO_config(void);
void DMA_ConfigChannel_2(uint32_t *pStartAddress, uint32_t *pDestination, uint32_t u32NumberDataTransfer);
void Light_Sensor(void);


#endif