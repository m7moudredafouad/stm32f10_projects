#include "gpio.h"
#include "uart.h"
#include "app.h"

void USART1_init(void) {
	/*			Map UART1 to USART1_REMAP = 1 (PB6(TX), {PB7(RX))		*/
	AFIO->MAPR |= UART1_REMAP;
	/* Initialize GPIOB6(USART1 TX) As Output (PUSH-PULL) (SPEED 10Mhz)	*/
	gpio_init(GPIOB, (GPIO_initialPropertiesType){6, GPIO_MODE_OP_SP_10, GPIO_CNF_AF_PP});
	gpio_init(GPIOB, (GPIO_initialPropertiesType){7, GPIO_MODE_IN, GPIO_CNF_IN_PP});
	
	RCC->APB2ENR |= UART1_CLOCK;	// Enable Clock for UART1
	
	/*			Initialize UART1		*/
	USART1->CR1 &= ~UART_CR1_W;	// Word lenght = 8 bits
	USART1->CR1 &= ~UART_CR1_PE;	// No parity
	
	USART1->CR2 &= ~UART_CR2_STOP;	// STOP BITS = 1
	
	/*			UART1 BAUD RATE 19200	= 234.37 => 0xEA2	*/
	USART1->BRR = 0xEA2;
}

void USART1_enable(void) {
	USART1->CR1 |= UART_CR1_UE;	// Enable USART1
	USART1->CR1 |= UART_CR1_TXENABLE | UART_CR1_TXIE;	// Enable Tx & Enable Tx interrupt
	USART1->CR1 |= UART_CR1_RXENABLE | UART_CR1_RXIE;	// Enable Rx & Enable Rx interrupt
	USART1->CR1 |= UART_CR1_PEIE;		// Enable Rx & Enable Rx interrupt
}

void USART_sndChar(USART_TypeDef * USARTx, unsigned char theChar) {
	while(!(USARTx->SR & UART_SR_TXE));
	USARTx->DR = theChar;
}

unsigned char USART_readChar(USART_TypeDef * USARTx) {
	while(!(USARTx->SR & UART_SR_RXNE));
	return (unsigned char) USARTx->DR;
}

void USART_sndStr(USART_TypeDef * USARTx, unsigned char *theChar, unsigned char *buffer,
	unsigned int *sndStart, unsigned int *sndEnd) {
	
	if(*sndStart == *sndEnd) *sndStart = *sndEnd = 0;
	unsigned char * p = theChar;
	
	(*sndEnd) %= MAX_BUFFER_SIZE;
	while(*p != '\0' && *sndEnd < MAX_BUFFER_SIZE) {
		while(buffer[*sndEnd] != '\0');	// Wait until the next char is sent 
		
		// Send the char
		buffer[(*sndEnd)++] = *p;
		p++;
	}
	
	if((USARTx->SR & UART_SR_TXE)) {
		USARTx->DR = buffer[(*sndStart)++];
		buffer[(*sndStart) - 1] = '\0';
	}
}


void USART1_IRQHandler(void) {
	// Transfer data register is empty
	if(USART1->SR & UART_SR_TXE) {
		unsigned char firstChar = APP_sndFirstChar();
		if(firstChar != '\0') {
			USART1->DR = firstChar;
		}
	}
	
	// Receive data is not empty and there is available data
	if (USART1->SR & UART_SR_RXNE) {
		APP_addRecivedChar((unsigned char) USART1->DR); 
	}
	
	
	if (USART1->SR & UART_SR_PE) {
		APP_sendParityMsg();
	}
}








