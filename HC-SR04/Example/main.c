#include"stm32f10x.h"
#include"HC_SR04.h"


float distance;
int main(){
		Delay_Systick_Init(72000000);
		 HC_SR04Init();
		while(1)
    {
        distance = Get_Distance();
        Delay_Systick_MS(60);
    }
}



