#include "stm32f10x.h"                  // Device header
#include "nvic.h"

void nvic_init(void) {
	NVIC_EnableIRQ(USART1_IRQn);
}
