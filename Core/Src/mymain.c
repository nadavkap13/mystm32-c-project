#include "mymain.h"
#include "main.h"
#include "mybuzzer.h"
#include "CLI.h"
#include "comtask.h"
#include "DHA_11.h"
#include "new_button.h"
#include "clock.h"
#include "MainTimer.h"
#include "potentiometer.h"
#include "Flash.h"
#include "LED.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lightsens.h"

int song[] = {
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_5,NOTE_1,NOTE_3,NOTE_4,
		NOTE_3,NOTE_3,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_4,NOTE_5,
		NOTE_1,NOTE_3,NOTE_4,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_4,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_4,
		NOTE_4,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_7,NOTE_7,
		NOTE_1,NOTE_1,
		NOTE_2,NOTE_4,NOTE_7,
		NOTE_1,NOTE_3,NOTE_4,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_2,NOTE_2,
		NOTE_4,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_4,
		NOTE_4,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_4,
		NOTE_1,NOTE_1,
		NOTE_3,NOTE_2,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_1,NOTE_1,
		NOTE_7,NOTE_7,
		NOTE_1,NOTE_1,
		NOTE_2,NOTE_4,NOTE_7,
		0
	};
int length[]={
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_1,FRAME_1,FRAME_2,FRAME_2,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_2,FRAME_2,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_2,FRAME_2,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_0,FRAME_1,
		FRAME_2,FRAME_2,FRAME_0,
		0

};

extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim1;
extern ADC_HandleTypeDef hadc1;

LIGHTSENS sensor;
LED ledred;
LED ledblue;
BUTTON button;
CLOCK clock;
BUZZER buzz;
ADC adc;
Function arry[100];
Function MainTimer_arry[100];
DHT dht;

uint32_t * flashdata = (uint32_t*)(0x08080000);
int i=0;
int startdelay=0;

uint32_t maxvalue = 10;
int DHTcount=0;
 uint8_t DHT_data[5];
int _write(int fd, char* ptr, int len)
{
      HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
      return len;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim4){
			  HAL_GPIO_WritePin(ledblue.GPIOx, ledblue.GPIO_Pin, 0);
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	//adcOnInterrupt(&adc,&buzz);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	Dht_onGpioInterrupt(&dht, GPIO_PIN_5);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	  if(htim == &htim6){
		  MainTimerInterrupt();


	  }
	  else if(htim==&htim4){
		  HAL_GPIO_WritePin(ledblue.GPIOx, ledblue.GPIO_Pin, 1);
	    }
}

//LED_STATE UPDATE(LED *led, int max) {
//	switch (LEDchangeState()) {
//	case LED_STATE_OFF:
//		ledOff(led);
//		break;
//	case LED_STATE_ON:
//		ledOn(led);
//		break;
//	case LED_STATE_BLINK:HAL_Delay(18);
//		ledBlink(led, max);
//		break;
//	}
//	return 0;
//}

int mymaininit()
{
	HAL_NVIC_EnableIRQ(TIM6_IRQn);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim6);
    HAL_ADC_Start_IT(&hadc1);
    HAL_TIM_Base_Start_IT(&htim4);
    HAL_TIM_Base_Start(&htim1);

    DHT_Init(&dht,GPIOB,GPIO_PIN_5);
    adcInit(&adc,&hadc1);
	lightsenseInit(&sensor, &hadc1, maxvalue);
	buttoninit(&button, SWO_GPIO_Port, SWO_Pin);
	ledInit(&ledred, RED_LED_GPIO_Port, RED_LED_Pin,TIM_CHANNEL_1,&htim4);
	ledInit(&ledblue, GPIOA, GPIO_PIN_5,TIM_CHANNEL_2,&htim4);

	clockInit(&clock,&htim6);
	buzzerInit(&buzz,&htim3);
	initCLI();
	eraseIT();

	char * read = (char*)(flashdata);
	printf(" string is %s\n\r",read);


	return 0;
}

int mymainloop()
{
	if (commTask()){
		 handleCommand();
	}

	if(Dht_hasData(&dht)){
		 printf("temp is : %d\n\r humid is : %d\r\n", DHT_data[2],DHT_data[0]);
	}
	return 0;
}

