#include <stdint.h>
#include <stdlib.h>
#include "new_button.h"
#include "main.h"

void buttoninit(BUTTON* button, GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin){
	button->GPIOx= GPIOx;
	button->GPIO_Pin=GPIO_Pin;
	 button->pushtime = 0;
	 button->relesetime = 0;
	 button->state=STATE_NOT_PRESSED;
}

void buttonpress(BUTTON* button){

	if(HAL_GPIO_ReadPin(button->GPIOx,button->GPIO_Pin)==0){
		button->pushtime = HAL_GetTick();
	}
	else {
		button->relesetime = HAL_GetTick();
		if(button->relesetime-button->pushtime < 500){
			 button->state = STATE_SHORT_PRESS;
		}
		else{
			 button->state = STATE_LONG_PRESS;
		}
	}
}
