#include"stm32f10x.h" 
#include"stm32f10x_gpio.h" 
#include"stm32f10x_rcc.h" 
#include"stm32f10x_tim.h" 
#include"DHT11.h"

int main() 
{ 
	//Timer2_Register(); 
	while(1)
	{ 
		DHT11_program(); 
		Delay_ms(1000); 
	} 
}

