#include "main.h"
#include "potentiometer.h"
#include "mymain.h"
#include "mybuzzer.h"
#include <stdio.h>

int tone=0;
int value=0;
extern TIM_HandleTypeDef htim3;

void adcInit(ADC* adc,ADC_HandleTypeDef *hadc){

	adc->hadc= hadc;
}
void adcOnInterrupt(ADC* adc,BUZZER* buzzer)
{
	value = HAL_ADC_GetValue(adc->hadc);
	printf("value ius %u\n\r",value);
	tone=((value/255)*915)+131;
	int period = 100000/tone;
	__HAL_TIM_SET_AUTORELOAD(buzzer->htim,period/2);
	__HAL_TIM_SET_COMPARE(buzzer->htim, TIM_CHANNEL_1,(period/2)/2);
	HAL_TIM_PWM_Start(buzzer->htim,TIM_CHANNEL_1);
}
