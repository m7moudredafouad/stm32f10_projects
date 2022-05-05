#ifndef GPOIO_H
#define GPOIO_H

#include "stm32f10x.h"                  // Device header
#include "main.h"

/*		Important definations		*/
#define GPIO_PIN_0 (1 << 0)
#define GPIO_PIN_1 (1 << 1)
#define GPIO_PIN_2 (1 << 2)
#define GPIO_PIN_3 (1 << 3)
#define GPIO_PIN_4 (1 << 4)
#define GPIO_PIN_5 (1 << 5)
#define GPIO_PIN_6 (1 << 6)
#define GPIO_PIN_7 (1 << 7)
#define GPIO_PIN_8 (1 << 8)
#define GPIO_PIN_9 (1 << 9)
#define GPIO_PIN_10 (1 << 10)
#define GPIO_PIN_11 (1 << 11)
#define GPIO_PIN_12 (1 << 12)
#define GPIO_PIN_13 (1 << 13)
#define GPIO_PIN_14 (1 << 14)
#define GPIO_PIN_15 (1 << 15)

#define PIN_SET (1)
#define PIN_RESET (0)

#define  GPIO_MODE_IN 			(0)
#define  GPIO_MODE_OP_SP_10 (1)
#define  GPIO_MODE_OP_SP_2 	(2)
#define  GPIO_MODE_OP_SP_50 (3)

#define GPIO_CNF_IN_ANALOG (0)
#define GPIO_CNF_IN_FLOATING (1)
#define GPIO_CNF_IN_PP (2)

#define GPIO_CNF_OP_PP (0)
#define GPIO_CNF_OP_OD (1)
#define GPIO_CNF_AF_PP (2)
#define GPIO_CNF_AF_OD (3)

typedef struct {
	uchar pinNumber: 4;
	uchar mode: 2;
	uchar cnf: 2;
} GPIO_initialPropertiesType;

/* 		Function Prototypes			*/
void GPIOx_EnablePortClock(GPIO_TypeDef * GPIOx, char enable);

void GPIOx_WritePin(GPIO_TypeDef * GPIOx, unsigned short pinNumber, char pinStatus);
void GPIOx_TogglePin(GPIO_TypeDef * GPIOx, unsigned short pinNumber);

uchar GPIOx_ReadPin(GPIO_TypeDef * GPIOx, unsigned short pinNumber);

void gpioa_init(void);

void gpio_init(GPIO_TypeDef * GPIOx, GPIO_initialPropertiesType props);

void gpio_initApp(void);

#endif // GPOIO_H
