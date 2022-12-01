#ifndef INC_LED_H_
#define INC_LED_H_
#include "main.h"

extern int countbrightness;

typedef enum _LED_STATE{
	LED_STATE_OFF,
	LED_STATE_ON,
	LED_STATE_BLINK
}LED_STATE;

typedef struct _LED{
	LED_STATE state;
	int count;
	int maxcount;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	uint32_t CHANNEL;
	TIM_HandleTypeDef* htim;
}LED;

void ledInit(LED* led,GPIO_TypeDef* port, uint16_t pin, uint32_t CHANNEL,TIM_HandleTypeDef* htim);
void ledOn(LED* led);
void ledOff(LED* led);
void ledBlink(LED* led, int period);
void ledOnTimerInterrupt(LED* led);
void ledOnPeriodicTask(LED* led);
void ledsetbrightness(LED* led,int brightness);
LED_STATE LEDchangeState();

#endif /* INC_LED_H_ */
