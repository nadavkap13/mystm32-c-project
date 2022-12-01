#ifndef INC_NEW_BUTTON_H_
#define INC_NEW_BUTTON_H_
#include <stdint.h>
#include <stdlib.h>
#include "main.h"

typedef enum{
	STATE_NOT_PRESSED,
	STATE_SHORT_PRESS,
	STATE_LONG_PRESS,
}BUTTON_STATE;

typedef struct _button{
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	uint32_t pushtime;
	uint32_t relesetime;
	BUTTON_STATE state;
}BUTTON;


void buttoninit(BUTTON* button, GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
void buttonpress(BUTTON* button);


#endif
