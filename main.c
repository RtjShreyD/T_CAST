#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_adc.h"
#include "clock.h"
#include "delay.h"
// USART library (USART1 on PB6 and PB7)
#include "usart.h"
#include <stdio.h>

// For ADC value
uint16_t adcValue = 0;
// For ADC value in string
char sAdcValue[50];

void ADC_Config(void)
{
    // Enable clock for ADC1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    // Init GPIOB for ADC input
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Init ADC1
    ADC_InitTypeDef ADC_InitStruct;
    ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_ExternalTrigConv = DISABLE;
    ADC_InitStruct.ADC_ExternalTrigConvEdge = 
        ADC_ExternalTrigConvEdge_None;
    ADC_InitStruct.ADC_NbrOfConversion = 1;
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = DISABLE;
    ADC_Init(ADC1, &ADC_InitStruct);
    ADC_Cmd(ADC1, ENABLE);

    // Select input channel for ADC1
    // ADC1 channel 9 is on PB1
    ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 1, 
        ADC_SampleTime_84Cycles);
}


uint16_t ADC_Read(void)
{
    // Start ADC conversion
    ADC_SoftwareStartConv(ADC1);
    // Wait until conversion is finish
    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));

    return ADC_GetConversionValue(ADC1);
}



int main(void)
{
    // Set clock to 168MHz
    // Don't forget to add defined symbol "HSE_VALUE=8000000"
    // in compile configuration
    CLOCK_SetClockTo168MHz();
    // Init delay function
    DELAY_Init();
    // Init USART
    // Here I'm using USART1 (PB6 Tx, PB7 Rx)
    USART_Config();
    // ADC config
    ADC_Config();
		USART_PutString("abcde");
	
    while (1)
    {
        // Read ADC value
        adcValue = ADC_Read();
        
				char c = adcValue;
				USART_PutChar(c);

        DELAY_Ms(1000);
    }
}
