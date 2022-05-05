#ifndef _APP_H
#define _APP_H
#include "main.h"
#include "gpio.h"


/*		Important definations		*/
#define MAX_BUFFER_SIZE (100)
#define CMD_SIZE (2)

/*			Type defination			*/
typedef enum {
	SEND_START_MSG,
	PROCESS_BUFFER,
	SEND_ERROR_CMD,
	NO_THING
} CMD_STATE;

typedef struct {
	uchar * name;
	void (*fn)(void);
} cmd_type;



void led_on(void);

void led_off(void);

/* 		Function Prototypes			*/
uchar  APP_sndFirstChar(void);
void APP_addRecivedChar(uchar theChar);
void APP_sendStartMsg(void);
void APP_sendNewLine(void);
void APP_sendParityMsg(void);
void APP_sendErrorCmd(void);
void APP_processCmd(void);
uchar string_cmp(uchar *str1, uchar * str2);
void APP_dispatchFn(uchar * cmd);

#endif