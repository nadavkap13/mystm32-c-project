#ifndef INC_POTENTIOMETER_H_
#define INC_POTENTIOMETER_H_
#include "mybuzzer.h"

typedef struct ADC{
	ADC_HandleTypeDef *hadc;
}ADC;

void adcInit(ADC* adc,ADC_HandleTypeDef *hadc);
//void adcOnInterrupt(ADC* adc,BUZZER* buzzer);

#endif /* INC_POTENTIOMETER_H_ */
