#include"DHT11.h"

volatile uint8_t Temp = 0;
volatile uint8_t Hum = 0;
volatile uint8_t float_temp = 0;
volatile uint8_t float_hum = 0;
volatile uint8_t checkSum = 0;
volatile uint8_t alive = 0;

void GPIO_configure(uint8_t mode) 
{ 
	GPIO_InitTypeDef GPIO_InitStructure; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); 
	GPIO_InitStructure.GPIO_Pin = DHT_PIN; 
	
	if(mode == 0) 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	else 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
}	

void Timer2_Register(void) 
{ 
	RCC->APB1ENR |= 0x01; //ENABLE Clock for timer2 
	TIM2->ARR = 0xFFFF; //TIMx auto-reload register (TIMx_ARR) 
	TIM2->PSC = 72 -1; //PSC[15:0]: Prescaler value 
	TIM2->CR1 = 0x01; //Bit 0 CEN: Counter enable and 0: counter used as upcounter; 
	TIM2->EGR = 0x01; //Generate an update event to reload the Prescaler and the Repetition counter value imediately; 
}
	
void Delay_us(uint32_t us) 
{ 
	uint32_t start = TIM2->CNT; 
	while((uint16_t)(TIM2->CNT - start) < us); 
} 
void Delay_ms(uint32_t ms) 
{ 
		while(ms--) 
		Delay_us(1000); 
}

uint8_t DHT11_Start()
{ 
	GPIO_configure(0); 
	GPIO_SetBits(DHT_PORT, DHT_PIN);
	GPIO_ResetBits(DHT_PORT, DHT_PIN); 
	Delay_ms(18); 
	GPIO_SetBits(DHT_PORT, DHT_PIN); 
	Delay_us(30); 
	GPIO_configure(1); //check 
	//check
	uint32_t timeout;
	// High to Low (80us)
	timeout = TIM2->CNT;
	while(GPIO_ReadInputDataBit(DHT_PORT,DHT_PIN))
	{ 
		if((TIM2->CNT - timeout) > 80) return 0; 
	}
	// Low to High(80us)
	timeout = TIM2->CNT;
	while(!GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)) 
	{ 
		if((TIM2->CNT - timeout) > 80) return 0; 
	} 
	// High to Low 
	timeout = TIM2->CNT; 
	while(GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)) 
	{ 
		if((TIM2->CNT - timeout) > 100) return 0; 
	} 
	return 1; 
}


uint8_t DHT_read_byte()
{ 
	uint8_t res = 0, i = 0; 
	for(i = 0; i < 8; i++) 
	{ 
		while(!GPIO_ReadInputDataBit(DHT_PORT,DHT_PIN));
		Delay_us(50); 
		if(GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)) 
			res = (res <<1) | (1<<0); 
		else res = (res <<1) & ~(1<<0); 
		while(GPIO_ReadInputDataBit(DHT_PORT, DHT_PIN)); 
	} 
	return res; 
}

void DHT11_program()
{		
		Timer2_Register();
    alive = DHT11_Start();
		
    if(alive)
    {
        Hum = DHT_read_byte();
        float_hum = DHT_read_byte();
        Temp = DHT_read_byte();
        float_temp = DHT_read_byte();
        checkSum = DHT_read_byte();

        if((Hum + float_hum + Temp + float_temp) != checkSum)
        {
            Temp = 0;
            Hum = 0;
        }
    }
}