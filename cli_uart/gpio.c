#include "gpio.h"												// Gpio header

/*		Function definations		*/
void GPIOx_EnablePortClock(GPIO_TypeDef * GPIOx, char enable) {
	if(enable) {
		if(GPIOx == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		else if(GPIOx == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		else return;
	} else {
		if(GPIOx == GPIOA) RCC->APB2ENR &= ~RCC_APB2ENR_IOPAEN;
		else if(GPIOx == GPIOB) RCC->APB2ENR &= ~RCC_APB2ENR_IOPBEN;
		else return;
	}
}

void GPIOx_WritePin(GPIO_TypeDef * GPIOx, unsigned short pinNumber, char pinStatus) {
	if(pinStatus) GPIOx->ODR |= pinNumber;
	else GPIOx->ODR &= ~pinNumber;
}

void GPIOx_TogglePin(GPIO_TypeDef * GPIOx, unsigned short pinNumber) {
	GPIOx->ODR ^= pinNumber;
}

uchar GPIOx_ReadPin(GPIO_TypeDef * GPIOx, unsigned short pinNumber){
	if(GPIOx->IDR & pinNumber) return PIN_SET;
	return PIN_RESET;
}

void gpioa_init(void) {
	// Enable clock for GPIOA
	GPIOx_EnablePortClock(GPIOA, 1);
	
	// Define GPIOA1 as output port with push-pull mode
	// We will work on pin 1
	//GPIOA->CRL &= (unsigned int)~(0xF << 4) | GPIO_CRL_MODE1_0;
	GPIOA->CRL = ((GPIOA->CRL & (unsigned int)~(0xF << 4)) | GPIO_CRL_MODE1_0);
	
	// Define GPIOA1 as output port with push-pull mode
	// We will work on pin 2
	//GPIOA->CRL &= (unsigned int)~(0xF << 4) | GPIO_CRL_MODE1_0;
	GPIOA->CRL |= ((GPIOA->CRL & (unsigned int)~(0xF << 8)) | GPIO_CRL_CNF2_1);
}

void gpio_init(GPIO_TypeDef * GPIOx, GPIO_initialPropertiesType props){
	unsigned int shift = (props.pinNumber % 8) * 4;
	
	if(props.pinNumber < 8) {
		GPIOx->CRL &= ~((unsigned int)(0xF << shift));
		// Initialize the mode and the config of the port
		GPIOx->CRL |= (unsigned int)(((props.cnf << 2) | props.mode) << shift);
		
	} else {
		GPIOx->CRH &= ~((unsigned int) (0xF << shift));
		GPIOx->CRH |= (unsigned int)(((props.cnf << 2) | props.mode) << shift);
	}
}


void gpio_initApp(void) {
// Enable clock for GPIOA
	GPIOx_EnablePortClock(GPIOA, PIN_SET);
	// Enable clock for GPIOB
	GPIOx_EnablePortClock(GPIOB, PIN_SET);
	
	// Initialize GPIOA1 As Output (PUSH-PULL) (SPEED 10Mhz)
	gpio_init(GPIOA, (GPIO_initialPropertiesType){1, GPIO_MODE_OP_SP_10, GPIO_CNF_OP_PP});
	// Initialize GPIOA2 As INPUT (PUSH-PULL)
	gpio_init(GPIOA, (GPIO_initialPropertiesType){2, GPIO_MODE_IN, GPIO_CNF_IN_PP});
}






