#include "Light_Sensor.h"


void GPIO_config(void){
		GPIO_InitTypeDef LED;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		LED.GPIO_Mode = GPIO_Mode_Out_PP;
		LED.GPIO_Pin  = GPIO_Pin_0;
		LED.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &LED);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void ADC_config(void){
		ADC_InitTypeDef ADC_InitStructure;
		ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
		ADC_InitStructure.ADC_ScanConvMode = DISABLE;
		ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStructure.ADC_NbrOfChannel = 1;
		ADC_Init(ADC1, &ADC_InitStructure);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);
		ADC_Cmd(ADC1, ENABLE);
		ADC_DMACmd(ADC1, ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));
		ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void DMA_ConfigChannel_2(uint32_t *pStartAddress, uint32_t *pDestination, uint32_t u32NumberDataTransfer){
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		DMA1_Channel1->CPAR = (uint32_t)pStartAddress;
		DMA1_Channel1->CMAR = (uint32_t)pDestination;
		DMA1_Channel1->CNDTR = u32NumberDataTransfer;
		DMA1_Channel1->CCR |= 0x2520;
		DMA1_Channel1->CCR |= 0x01;
}

void Delay_ms(uint32_t time){
		while(time){
			SysTick->LOAD = 72U *1000U-1U;
			SysTick->VAL = 0U;
			SysTick->CTRL = 5U;
			while(!(SysTick->CTRL & (1U<<16U)));
			--time;
		}
}

	
	
