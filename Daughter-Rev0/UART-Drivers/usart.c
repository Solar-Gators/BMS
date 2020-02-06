#include "stm32f10x.h"

void init_usart3(uint32_t baud)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	// 36MHz
	
	RCC_ClocksTypeDef clocks;
	RCC_GetClocksFreq(&clocks);
	
	f_ck = clocks.PCLK1_Frequency;
	
	uint32_t div = 
	
	// 125kbps = 36 = 0x240
	// 250kbps = 18 = 0x120
	// 500kbps = 9	= 0x090
	// 1mbps = 4.5	= 0x048

	// USART->BRR |= 
	
}