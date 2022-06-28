#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "mymain.h"
#include "mybuzzer.h"
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
int count = 0;
uint32_t frame;
void buzzerInit(BUZZER* buzzer,TIM_HandleTypeDef *htim){
	buzzer->htim = htim;
}
void buzzerStartPlay(BUZZER* buzzer,int* song, int* frames){
	buzzer->song = song;
	buzzer->frames = frames;

	__HAL_TIM_SET_AUTORELOAD(&htim3,buzzer->song[count]/2);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,((buzzer->song[count]/2)/2));
	HAL_TIM_Base_Start(&htim3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}
void buzzerStopPlay(){
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}

void buzzerOnInterrupt(BUZZER* buzzer){
	frame++;
	if(frame >= buzzer->frames[count] ){
		__HAL_TIM_SET_COUNTER(&htim3,0);
		__HAL_TIM_SET_AUTORELOAD(&htim3,buzzer->song[count]/2);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1,((buzzer->song[count]/2)/2));
		count++;
		frame = 0;
	}
	if(buzzer->song[count]==0 && buzzer->frames[count]== 0){
		count=0;
	}
}

















