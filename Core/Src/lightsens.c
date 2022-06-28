#include <stdint.h>
#include <stdlib.h>
#include "lightsens.h"
#include "main.h"

void lightsenseInit(LIGHTSENS* sensor, ADC_TypeDef* ADC,uint32_t maxvalue){
	sensor->ADC = ADC;
	sensor->maxvalue = maxvalue;
	sensor->minvalue = 0;
}

int getValue(LIGHTSENS* sensor){
	return ((sensor->maxvalue * sensor->value)+(4095/2)) / 4095;
}

