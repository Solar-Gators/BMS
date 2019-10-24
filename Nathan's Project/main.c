#include "stm32f10x.h"

GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;

volatile uint16_t count = 0;
volatile uint16_t result = 0;

void InitGPIO()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void InitADC()
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1    , ENABLE );     //Enable GPIOA, ADC1 channel clock
	RCC_ADCCLKConfig(RCC_PCLK2_Div6); //The 6 72M clock frequency factor/6=12MHz

	ADC_DeInit(ADC1); //All the register peripheral ADC1 is reset to the default values
	
	ADC1->CR1 |= ADC_CR1_EOCIE;
	ADC1->CR2 |= ADC_CR2_TSVREFE + ADC_CR2_EXTTRIG + ADC_ExternalTrigConv_None + ADC_CR2_CONT;
	
	ADC1->SMPR1 |= 0x001C0000;
	ADC1->SQR3 |= 0x00000010;
	
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

void InitTimer()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM2->DIER |= TIM_DIER_UIE;
	TIM2->PSC = 0xF0;
	TIM2->ARR = 0x7000;
	TIM2->CR1 |= TIM_CR1_CEN;
}

int main()
{
	InitGPIO();
	
	NVIC_SetPriority(TIM2_IRQn,20);
	NVIC_EnableIRQ(TIM2_IRQn);
	InitTimer();
	
	NVIC_SetPriority(ADC1_2_IRQn,25);
	NVIC_EnableIRQ(ADC1_2_IRQn);
	InitADC();
	
	GPIOA->BSRR = GPIO_Pin_9;
	
	while (1)
	{
		
	}
}

void ADC1_2_IRQHandler(void)
{
	if (ADC1->SR & ADC_SR_EOC)
	{
		count++;
		result = (ADC1->DR & 0xFFF);
		ADC1->SR &= ~(ADC_SR_EOC);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM2->SR & TIM_SR_UIF)
	{
		GPIOA->ODR ^= (GPIO_Pin_9 + GPIO_Pin_10);
		TIM2->SR &= ~(TIM_SR_UIF);
	}
}
