#include "mybuzzer.h"
#include "new_button.h"
#include "LED.h"
#include "comtask.h"
#include "clock.h"
#include "mymain.h"
#include "main.h"
#include "DHA_11.h"
#include "MainTimer.h"
extern CLOCK clock;
extern DHT dht;
extern LED ledblue;
extern BUZZER buzz;
extern MainTimer_Function MainTimer_arry[100];
int MainTimer_funcounter = 0;


void MainTimerInit(MAINTIMER *maintimer, TIM_HandleTypeDef *htim) {
	maintimer->htim = htim;
}
void MainTimer_registerCallback(HandlerMainTimer_Func TIMER_Func, void *obj) {
	MainTimer_arry[MainTimer_funcounter].TIMER_Func = TIMER_Func;
	MainTimer_arry[MainTimer_funcounter].obj = obj;
	MainTimer_funcounter++;
}
void mainTimerLed(void *obj) {
	LED *led = (LED*) obj;
	ledOnTimerInterrupt(led);
}
void mainTimerBuzzer(void *obj) {
	BUZZER *buzzer = (BUZZER*) obj;
	buzzerOnInterrupt(buzzer);
}
void mainTimerClock(void *obj) {
	CLOCK *clock = (CLOCK*) obj;
	clockInInterrupt(clock);
}
void mainTimerDht(void *obj) {
	DHT *dht = (DHT*) obj;
	DHT_onTimerInteruppt(dht);
}

void MainTimer_UnregisterCallback(HandlerMainTimer_Func TIMER_Func, void *obj) {
	int remove = 0;
	int boolcount = 0;

	for (int j = 0; j < MainTimer_funcounter; j++) {
		if (MainTimer_arry[j].TIMER_Func == TIMER_Func && MainTimer_arry[j].obj == obj) {
			MainTimer_arry[j].TIMER_Func = NULL;
			MainTimer_arry[j].obj = NULL;
			remove = 1;
			boolcount = j;
			break;
		}
	}

	if (remove == 1 && MainTimer_funcounter > 0) {
		MainTimer_funcounter--;
		MainTimer_arry[boolcount].TIMER_Func = MainTimer_arry[MainTimer_funcounter].TIMER_Func;
		MainTimer_arry[boolcount].obj = MainTimer_arry[MainTimer_funcounter].obj;
	}
}

void MainTimerInterrupt() {
	for (int j = 0; j < MainTimer_funcounter; j++) {

		MainTimer_arry[j].TIMER_Func(MainTimer_arry[j].obj);
	}

}
