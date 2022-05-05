#include "stm32f10x.h"                  // Device header
#include "gpio.h"												// GPIO header
#include "uart.h"												// UART header
#include "nvic.h"												// NVIC header
#include "app.h"


/* 		Function Prototypes			*/

/*		Main Programe			*/
int main(){
	/*		Initializations		*/
	nvic_init();			// Initialize NVIC
	gpio_initApp();		// Initialize GPIO
	USART1_init();			// Initialize UART1	
	USART1_enable();
	
	__enable_irq();

	/*	 Variable declaration		*/
	unsigned char btnVal;

	/*		Main App		*/
	// GPIOx_WritePin(GPIOA, GPIO_PIN_1, PIN_SET);
	while(1) {
		//btnVal = GPIOx_ReadPin(GPIOA, GPIO_PIN_2);
		
		APP_processCmd();
		
	}
}


