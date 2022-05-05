#ifndef UART_H
#define UART_H

#include "stm32f10x.h"                  // Device header

/*		Important definations		*/
#define UART1_CLOCK 			(1 << 14)
#define UART1_REMAP 			(1 << 2)

#define UART_CR1_UE 			(1 << 13)
#define UART_CR1_W 				(1 << 12)
#define UART_WAKE_METHOD 		(1 << 11)
#define UART_CR1_PE 			(1 << 10)
#define UART_CR1_PSEL	 		(1 << 9)
#define UART_CR1_PEIE 			(1 << 8)
#define UART_CR1_TXIE 			(1 << 7)
#define UART_CR1_TCIE 			(1 << 6)
#define UART_CR1_RXIE 			(1 << 5)
#define UART_IDL_IE 			(1 << 4)
#define UART_CR1_TXENABLE 		(1 << 3)
#define UART_CR1_RXENABLE 		(1 << 2)
#define UART_RX_WAKEUP 			(1 << 1)
#define UART_SEND_BREAK 		(1 << 0)

#define UART_CR2_STOP			((1 << 12) | (1 << 13))

#define UART_SR_PE 				(1 << 0)
#define UART_SR_RXNE 			(1 << 5)
#define UART_SR_TXC 			(1 << 6)
#define UART_SR_TXE 			(1 << 7)


/* 		Function Prototypes			*/
void USART1_init(void);
void USART1_enable(void);

void USART_sndChar(USART_TypeDef * USARTx, unsigned char theChar);
void USART_sndStr(USART_TypeDef * USARTx, unsigned char *theChar, unsigned char *buffer,
	unsigned int *sndStart, unsigned int *sndEnd);

unsigned char USART_readChar(USART_TypeDef * USARTx);


#endif // UART_H
