#include "main.h"
#include "mymain.h"
#include "clock.h"
#include "MainTimer.h"

void clockInit(CLOCK* clock,TIM_HandleTypeDef *htim){
	clock->htim = htim;
	clock->tick_counter = 0;
	//clock->state = CLOCK_STATE_OFF;
	MainTimer_registerCallback(&mainTimerClock,clock);
}
void getClockTick(CLOCK* clock,uint32_t* tick){
	*tick = clock->tick_counter;
}
void getTime( CLOCK* clock, uint32_t* sec,uint32_t* min, uint32_t* hour){
	*sec = (clock->tick_counter/1000);
	*min = *sec / 60;
	*sec = *sec % 60;
	*hour = *min / 60;
	*min = *min % 60;
}
void clockInInterrupt(CLOCK* clock){
	clock->tick_counter++;
}
