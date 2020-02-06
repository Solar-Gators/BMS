#ifndef BMS_USART_H
#define BMS_USART_H

#include "stm32f10x.h"


#define USART3_125K_BRR 0x240
#define USART3_250K_BRR 0x120
#define USART3_500K_BRR 0x090
#define USART3_1M_BRR 0x048

void init_usart(uint32_t baud);

#endif