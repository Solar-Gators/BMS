
#include "ADC_Driver.h"

void ADC_init(void)
{
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);     //Enable GPIOA, ADC1 channel clock
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //The 6 72M clock frequency factor/6=12MHz
	
	ADC_DeInit(ADC1);
	
	ADC1->CR1 = ADC_CR1_EOCIE;
	
	
	
}