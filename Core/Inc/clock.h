#ifndef INC_CLOCK_H_
#define INC_CLOCK_H_
#include "main.h"

typedef enum {
	CLOCK_STATE_ON,
	CLOCK_STATE_OFF
}CLOCK_STATE;

typedef struct _CLOCK{
	TIM_HandleTypeDef *htim;
	uint32_t tick_counter;
	CLOCK_STATE* state;

}CLOCK;

void clockInit(CLOCK* clock,TIM_HandleTypeDef *htim);
void getClockTick(CLOCK* clock,uint32_t* tick);
void getTime( CLOCK* clock, uint32_t* sec,uint32_t* min, uint32_t* hour);
void clockInInterrupt(CLOCK* clock);
#endif /* INC_CLOCK_H_ */
