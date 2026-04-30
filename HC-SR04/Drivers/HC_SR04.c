#include "HC_SR04.h"

static uint32_t ticks_per_us = 0;

void Delay_Systick_Init(uint32_t clk){
    ticks_per_us = clk / 1000000U;
    SysTick->CTRL = 0;
    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = (1U<<0) | (1U<<2);
}

void Delay_Systick_US(uint32_t time_us){
    uint32_t ticks = time_us * ticks_per_us;
    SysTick->LOAD = ticks - 1U;
    SysTick->VAL = 0;
    while((SysTick->CTRL & (1U<<16)) == 0);
}

void Delay_Systick_MS(uint32_t time_ms){
    while(time_ms--){
        Delay_Systick_US(1000);
    }
}


void HC_SR04_Timer_Init(void) {

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 
    TIM2->PSC = 72 - 1;       
    TIM2->ARR = 0xFFFF;       
    TIM2->CR1 |= TIM_CR1_CEN; 
}


void HC_SR04Init(void)
{
    GPIO_InitTypeDef HC_SR04;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    HC_SR04.GPIO_Pin = TRIG_Pin;
    HC_SR04.GPIO_Mode = GPIO_Mode_Out_PP;
    HC_SR04.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &HC_SR04);  
    HC_SR04.GPIO_Pin = ECHO_Pin;
    HC_SR04.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &HC_SR04); 
    HC_SR04_Timer_Init();
    GPIO_ResetBits(GPIOA, TRIG_Pin);
}


void HC_SR04_TRIG(void){
    GPIO_ResetBits(GPIOA, TRIG_Pin);
    Delay_Systick_US(2);
    GPIO_SetBits(GPIOA, TRIG_Pin);
    Delay_Systick_US(10);
    GPIO_ResetBits(GPIOA, TRIG_Pin);
}

uint32_t HC_SR04_ECHO(void){
    uint32_t timeout;
    timeout = 1000000; 
    while ((GPIOA->IDR & ECHO_Pin) == 0) { 
        if (--timeout == 0) return 0; 
    }

    TIM2->CNT = 0;

    timeout = 1000000;
    while ((GPIOA->IDR & ECHO_Pin) != 0) {
        if (--timeout == 0) break;
    }
    return TIM2->CNT; 
}

float Get_Distance(void){
    uint32_t echo_time;   
    HC_SR04_TRIG();
    echo_time = HC_SR04_ECHO();
    if (echo_time == 0) {
        return -1.0f; 
    }
    return (float)echo_time / 58.0f; 
}