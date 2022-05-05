#include "uart.h"
#include "app.h"

#define TO_LOWER(c) ((c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c);

/*		Variables		*/
static CMD_STATE processState = SEND_START_MSG;

static uchar USART1_sendBuffer[MAX_BUFFER_SIZE],
						USART1_recieveBuffer[MAX_BUFFER_SIZE];

static unsigned int USART1_sndStart = 0, USART1_sndEnd = 0,
					USART1_rcvEnd = 0;

static cmd_type CMD_ARR[] = {
	{(uchar *) "led_on", led_on},
	{(uchar *) "led_off", led_off},
};

void led_on(void) {
	GPIOx_WritePin(GPIOA, GPIO_PIN_1, PIN_SET);
}

void led_off(void) {
	GPIOx_WritePin(GPIOA, GPIO_PIN_1, PIN_RESET);
}


/*		Function definations		*/
uchar APP_sndFirstChar(void) {
	USART1_sndStart %= MAX_BUFFER_SIZE;

	unsigned char sndChar = USART1_sendBuffer[USART1_sndStart];
	if(sndChar != '\0') {
		USART1_sendBuffer[USART1_sndStart++] = '\0';
	}
	return sndChar;
}

void APP_addRecivedChar(uchar theChar) {
	if(theChar == '\r' || USART1_rcvEnd >= MAX_BUFFER_SIZE - 1) {
		theChar = '\0';
		processState = PROCESS_BUFFER;
	}
	
	USART1_recieveBuffer[USART1_rcvEnd++] = TO_LOWER(theChar);
	USART1_recieveBuffer[USART1_rcvEnd] = '\0';
	
	USART1_rcvEnd %= MAX_BUFFER_SIZE;

}

void APP_sendNewLine(void) {
	USART_sndStr(USART1, (uchar *)">", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
}

void APP_sendStartMsg(void) {
	USART_sndStr(USART1, (uchar *)">Hello this is cmd\r", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
	
	USART_sndStr(USART1, (uchar *)">Please enter your command\r>", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
}

void APP_sendParityMsg(void) {
	USART_sndStr(USART1, (uchar *)">Parity Error\r", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
	
	USART_sndStr(USART1, (uchar *)">Please enter your command\r>", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
}

void APP_sendErrorCmd(void) {
	USART_sndStr(USART1, (uchar *)"Command is not available\r>", USART1_sendBuffer,
		&USART1_sndStart, &USART1_sndEnd);
}

void APP_processCmd(void) {
	switch(processState) {
		case SEND_START_MSG:
			APP_sendStartMsg();
			processState = NO_THING;
		break;
		case PROCESS_BUFFER:
			APP_dispatchFn(USART1_recieveBuffer);
		break;
		case SEND_ERROR_CMD:
			APP_sendErrorCmd();
			processState = NO_THING;

		break;
		case NO_THING:
		break;
	}
}

void APP_dispatchFn(uchar * cmd) {
	USART1->CR1 &= ~UART_CR1_UE;	// disable USART1

	int i = 0;
	for(i = 0; i < CMD_SIZE; i++) {
		if (string_cmp(cmd, CMD_ARR[i].name)) {
			break;
		}
	}
	USART1_rcvEnd = 0;
	USART1->CR1 |= UART_CR1_UE;	// Enable USART1
	
	if(i < CMD_SIZE) {
		CMD_ARR[i].fn();
		processState = NO_THING;
		APP_sendNewLine();
	} else {
		processState = SEND_ERROR_CMD;
	}
}


uchar string_cmp(uchar *str1, uchar * str2) {
	uchar * p1 = str1, *p2 = str2;
	while(*p1 == *p2) {
		if(*p1 == '\0') return 1;
		p1++;
		p2++;
	}
	return 0;
}



