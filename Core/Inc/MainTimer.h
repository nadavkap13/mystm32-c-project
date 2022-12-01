#ifndef INC_MAINTIMER_H_
#define INC_MAINTIMER_H_
#include "main.h"
#include <stdint.h>

typedef void (*HandlerMainTimer_Func)(void*);

typedef struct MainTimer_function{

	HandlerMainTimer_Func TIMER_Func;
	void* obj;
}MainTimer_Function;

typedef struct _MAINTIMER{
	TIM_HandleTypeDef *htim;

}MAINTIMER;

void MainTimerInterrupt();
void MainTimer_registerCallback(HandlerMainTimer_Func TIMER_Func,void* obj);
void mainTimerLed(void*obj);
void mainTimerBuzzer(void* obj);
void mainTimerClock(void* obj);
void mainTimerDht(void* obj);
void MainTimer_UnregisterCallback(HandlerMainTimer_Func TIMER_Func,void* obj);
void MainTimerInit(MAINTIMER* maintimer,TIM_HandleTypeDef* htim);
#endif /* INC_MAINTIMER_H_ */
