#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

void Delay(__IO uint32_t nCount)
{
    while (nCount--);
}

int main(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		
    
		GPIO_InitTypeDef GPIO_InitDef;
    
		GPIO_InitDef.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitDef.GPIO_OType = GPIO_OType_PP;
    GPIO_InitDef.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOD, &GPIO_InitDef);
	

    while (1)
    {
      GPIOD->ODR = 0x6000; //Set PG13 and PG14 high
			Delay(1000000);
			GPIOD->ODR = 0; 
			Delay(1000000);
			
					
    }
}

