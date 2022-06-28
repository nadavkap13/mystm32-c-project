#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mymain.h"
#include "main.h"
#include "mybuzzer.h"
#include "lightsens.h"
int i=0;
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
extern ADC_HandleTypeDef hadc1;
#define MAX_BUFFER_LENGTH 100

uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;
uint32_t tick = 0;
uint32_t sec = 0;
uint32_t min =0;
uint32_t hour =0;
uint32_t maxvalue = 10;
LIGHTSENS sensor;
LED ledred;
LED ledblue;
BUTTON button;
CLOCK clock;
BUZZER buzz;
int _write(int fd, char* ptr, int len) {
      HAL_UART_Transmit(&huart2, (uint8_t *) ptr, len, HAL_MAX_DELAY);
      return len;
  }
int commTask()
{
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK)
	{
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0)
		{
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount)
		{
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n')
	{
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH)
		{
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount)
	{
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)"\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}

void handleCommand()
{
  char cmd[20];
  int maxCount;

  int params = sscanf((const char*)cmdbuffer, "%s %d", cmd, &maxCount);

  if (params == 0)
  {
	  return;
  }

  if (strcmp(cmd, "startled") == 0)
  {
	  ledOn(&ledblue);
	  ledOn(&ledred);


  }
  else if (strcmp(cmd, "stopled") == 0)
  {
	  ledOff(&ledred);
	  ledOff(&ledblue);


  }
  else if (strcmp(cmd, "ledblink") == 0)
   {
	 ledBlink(&ledred, maxCount);
	 ledBlink(&ledblue, maxCount);
   }
  else if (strcmp(cmd, "setled") == 0)
   {
	  HAL_TIM_Base_Start_IT(&htim4);
	  ledsetbrightness(&ledred,maxCount);

	  //ledsetbrightness(&ledblue,maxCount);
   }
  else if (strcmp(cmd, "gettick") == 0)
    {
 	  getClockTick(&clock, &tick);
 	  printf("tick is %u\n\r", tick);
    }
  else if (strcmp(cmd, "gettime") == 0)
    {
 	  getTime(&clock, &sec, &min, &hour);
	  printf("time is %zu,%zu,%zu\n\r", hour, min, sec);
    }

  else if (strcmp(cmd, "startbuzzer") == 0)
   {
	  buzzerStartPlay(&buzz, song, length);
   }
  else if (strcmp(cmd, "stopbuzzer") == 0)
   {
	  buzzerStopPlay();
   }
  else
  {
	  printf("Invalid command\r\n");
  }
}
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim==&htim4){
		  HAL_GPIO_WritePin(ledred.GPIOx, ledred.GPIO_Pin, 0);
	}
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	sensor.value = HAL_ADC_GetValue(sensor.ADC);
}
  void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

  }
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	  if(htim == &htim6){
		  clockInInterrupt(&clock);
		  buzzerOnInterrupt(&buzz);
		  ledOnTimerInterrupt(&ledblue);
		  ledOnTimerInterrupt(&ledred);


	  }
	  else if(htim==&htim4){
		  HAL_GPIO_WritePin(ledred.GPIOx, ledred.GPIO_Pin, 1);
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
//	case LED_STATE_BLINK:
//		ledBlink(led, max);
//		break;
//	}
//	return 0;
//}
int maininit(){
	HAL_NVIC_EnableIRQ(TIM6_IRQn);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_Base_Start_IT(&htim6);
    HAL_ADC_Start_IT(&hadc1);
    HAL_TIM_Base_Start_IT(&htim4);

	lightsenseInit(&sensor, &hadc1, maxvalue);
	buttoninit(&button, SWO_GPIO_Port, SWO_Pin);
	ledInit(&ledred, RED_LED_GPIO_Port, RED_LED_Pin,TIM_CHANNEL_1,&htim4);
	ledInit(&ledblue, GPIOA, GPIO_PIN_5,TIM_CHANNEL_2,&htim4);

	HAL_TIM_PWM_Start_IT(ledred.htim, ledred.CHANNEL);
	clockInit(&clock,&htim6);
	buzzerInit(&buzz,&htim3);
	return 0;
}
int mainloop(){
	 if (commTask())
	 {
		 handleCommand();
	 }

	 ledsetbrightness(&ledred, getValue(&sensor));
	return 0;
}

