#include "stm32f10x.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "Light_Sensor.h"


uint32_t ValueADCChannel = 0; 

int main(){
		GPIO_config();
		ADC_config();
		DMA_ConfigChannel_2((uint32_t*)ADC1_DR_ADDRESS, (uint32_t*)&ValueADCChannel, 1);
		while(1){
		if(ValueADCChannel > 2100U){
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
		}else{
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);	
		}
	}
}


