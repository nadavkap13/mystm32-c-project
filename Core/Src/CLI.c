#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "CLI.h"
#include "mybuzzer.h"
#include "new_button.h"
#include "LED.h"
#include "comtask.h"
#include "clock.h"
#include "mymain.h"
#include "main.h"
#include "DHA_11.h"
#include "MainTimer.h"
#include "Flash.h"

extern CLOCK clock;
extern DHT dht;
extern LED ledblue;
extern BUZZER buzz;
extern int length[];
extern int song[];
extern uint8_t DHT_data[5];
static uint32_t  tick=0;
static uint32_t sec = 0;
static uint32_t min =0;
static uint32_t hour =0;
void cmdLedon(void* obj,char* params)
{
	HAL_TIM_PWM_Stop_IT(ledblue.htim, ledblue.CHANNEL);
	LED* led = (LED*)obj;
	ledOn(led);
}
void cmdLedoff(void* obj,char* params)
{
	HAL_TIM_PWM_Stop_IT(ledblue.htim, ledblue.CHANNEL);
	LED* led = (LED*)obj;
	ledOff(led);
}
void cmdledblink(void* obj,char* params)
{
	HAL_TIM_PWM_Stop_IT(ledblue.htim, ledblue.CHANNEL);
	LED* led = (LED*)obj;
	int blink= atoi(params);
	ledBlink(led, blink);
}
void cmdledbright(void* obj,char* params)
{
	LED* led = (LED*)obj;
	int bright= atoi(params);
	ledsetbrightness(led, bright);
	HAL_TIM_PWM_Start_IT(ledblue.htim, ledblue.CHANNEL);
}
void cmdClockTick(void* obj,char* params)
{
	CLOCK* clock = (CLOCK*)obj;
	getClockTick(clock,&tick);
	printf("tick is %lu\n\r", tick);
}
void cmdClockTime(void* obj,char* params)
{
	CLOCK* clock = (CLOCK*)obj;
	getTime(clock, &sec, &min, &hour);
	printf("time is %lu,%lu,%lu\n\r", hour, min, sec);
}

void cmdBuzzerStartPlay(void* obj,char* params)
{
	BUZZER* buzzer = (BUZZER*)obj;
	buzzerStartPlay(buzzer,song, length);
}
void cmdBuzzerStopPlay(void* obj,char* params)
{
	BUZZER* buzzer = (BUZZER*)obj;
	buzzerStopPlay(buzzer);
}
void cmdGetTempAndHumidity(void* obj,char* params){
	DHT* dht =(DHT*)obj;
	Dht_readAsync(dht);

}
void initCLI()
{
	 RegisterCommand("ledon",cmdLedon,&ledblue);
	 RegisterCommand("ledoff",cmdLedoff,&ledblue);
	 RegisterCommand("ledblink",cmdledblink,&ledblue);
	 RegisterCommand("ledset",cmdledbright,&ledblue);
	 RegisterCommand("gettick",cmdClockTick,&clock);
	 RegisterCommand("gettime",cmdClockTime,&clock);
	 RegisterCommand("buzzerplay",cmdBuzzerStartPlay, &buzz);
	 RegisterCommand("buzzerstop",cmdBuzzerStopPlay, &buzz);
	 RegisterCommand("gettemp",cmdGetTempAndHumidity,&dht);
}

