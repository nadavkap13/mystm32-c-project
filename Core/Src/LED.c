#include "LED.h"
#include "main.h"
#include "MainTimer.h"
#include <stdio.h>
extern TIM_HandleTypeDef htim4;
extern int MainTimer_funcounter;

void ledInit(LED* led,GPIO_TypeDef* port, uint16_t pin, uint32_t CHANNEL,TIM_HandleTypeDef* htim){
	led->state = LED_STATE_OFF;
	led->count = 0;
	led->GPIOx= port;
	led->GPIO_Pin=pin;
	led->maxcount=0;
	led->CHANNEL=CHANNEL;
	led->htim = htim;

}
void ledOn(LED* led)
{
	led->state = LED_STATE_ON;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 1);
	MainTimer_UnregisterCallback(mainTimerLed,led);
	printf("count is %d\n\r",MainTimer_funcounter);
}
void ledOff(LED* led)
{
	led->state = LED_STATE_OFF;
	HAL_GPIO_WritePin(led->GPIOx, led->GPIO_Pin, 0);
	MainTimer_UnregisterCallback(mainTimerLed,led);
}
void ledBlink(LED* led, int period)
{
	led->state = LED_STATE_BLINK;
	led->maxcount=period;
	MainTimer_registerCallback(mainTimerLed,led);
	printf("count is %d\n\r",MainTimer_funcounter);
}
void ledOnTimerInterrupt(LED* led)
{
	if(led->state== LED_STATE_BLINK){
	if (led->count >= led->maxcount){
			HAL_GPIO_TogglePin(led->GPIOx, led->GPIO_Pin);
			led->count = 0;
		}
	}
			led->count++;
}
void ledOnPeriodicTask(LED* led)
{

}

LED_STATE currentstate = LED_STATE_OFF;
LED_STATE LEDchangeState()
{
	switch (currentstate){
	case LED_STATE_OFF:
		currentstate = LED_STATE_ON;
		break;
	case LED_STATE_ON:
			currentstate = LED_STATE_BLINK;
			break;
	case LED_STATE_BLINK:
			currentstate = LED_STATE_OFF;
			break;
	}

	return currentstate;
}
void ledsetbrightness(LED* led,int brightness)
{
	brightness= (brightness*10);
	__HAL_TIM_SET_COMPARE(led->htim,led->CHANNEL, brightness);
}
