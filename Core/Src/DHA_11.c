#include "main.h"
#include "DHA_11.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "MainTimer.h"

static uint8_t dht_byte= 0;
static int dht_count=0;
static uint8_t m= 0;
static uint8_t p= 0;
GPIO_InitTypeDef gpioStruct;
extern uint8_t DHT_data[5];
 int delay=0;
extern int startdelay;
extern TIM_HandleTypeDef htim1;
void DHT_Init(DHT* dht,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	dht->GPIO_Pin = GPIO_Pin;
	dht->GPIOx= GPIOx;
	dht->dhtPin = WAKING;
	dht->bitcount=0;

}
//int DHTRead()
//{
//
//	GPIO_InitTypeDef gpioStruct;
//	gpioStruct.Pin = D4_Pin;
//	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	gpioStruct.Pull = GPIO_NOPULL;
//	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(D4_GPIO_Port, &gpioStruct);
//
//	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin,0);
//
//if (delay==1){
//	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin,1);
//
//	while(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==1){
//		gpioStruct.Pin = D4_Pin;
//		gpioStruct.Mode = GPIO_MODE_INPUT;
//		gpioStruct.Pull = GPIO_NOPULL;
//		gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
//		HAL_GPIO_Init(D4_GPIO_Port, &gpioStruct);
//
//	}
//	while(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==0){
//	}
//	if(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==0){
//	return 0;
//	}
//
//
//	__HAL_TIM_SET_COUNTER(&htim1, 0);
//	while(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==1 && __HAL_TIM_GET_COUNTER(&htim1)<=120 ){}
//
//		if(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==1){
//			return 0;
//		}
//
//
//	__HAL_TIM_SET_COUNTER(&htim1, 0);
//	while(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==0 && __HAL_TIM_GET_COUNTER(&htim1)<=120);
//	if(HAL_GPIO_ReadPin(D4_GPIO_Port, D4_Pin)==0){
//				return 0;
//			}
//}
//	return 1;
//}
int DHTResponse()
{

for (int b=0;b<5;b++){
			uint8_t i = 0,j = 0;
			for (j=0;j<8;j++)
			{
				while (!(HAL_GPIO_ReadPin (D4_GPIO_Port, D4_Pin)));   // wait for the pin to go high
				__HAL_TIM_SET_COUNTER(&htim1, 0);
				while(__HAL_TIM_GET_COUNTER(&htim1)<=50);
				if (!(HAL_GPIO_ReadPin (D4_GPIO_Port, D4_Pin)))   // if the pin is low
				{
					i&= ~(1<<(7-j));   // write 0
				}
				else i|= (1<<(7-j));  // if the pin is high, write 1
				__HAL_TIM_SET_COUNTER(&htim1, 0);
				while ((HAL_GPIO_ReadPin (D4_GPIO_Port, D4_Pin) && __HAL_TIM_GET_COUNTER(&htim1)<=120));  // wait for the pin to go low
			}
			if (i==255){
				return 0;
			}
			DHT_data[b]=i;
	}
return 1;
}

static void setGpioExti(DHT* dht)
{
	GPIO_InitTypeDef gpioStruct = {0};
	gpioStruct.Pin = dht->GPIO_Pin;
	gpioStruct.Mode = GPIO_MODE_IT_FALLING;
	gpioStruct.Pull = GPIO_PULLUP;

	HAL_GPIO_Init(dht->GPIOx, &gpioStruct);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void Dht_readAsync(DHT* dht)
{
	GPIO_InitTypeDef gpioStruct;
	gpioStruct.Pin = D4_Pin;
	gpioStruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioStruct.Pull = GPIO_NOPULL;
	gpioStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(D4_GPIO_Port, &gpioStruct);

	HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin,0);
	//startdelay=1;
	//MainTimer_registerCallback(mainTimerDht,dht);

	HAL_Delay(18);
	//if(delay==1){
	setGpioExti(dht);
	//MainTimer_UnregisterCallback(mainTimerDht,dht);
	//}
}

void Dht_onGpioInterrupt(DHT* dht, uint16_t pin)
{
	uint32_t counter;
	if(dht->GPIO_Pin==pin){
		switch (dht->dhtPin){
		case WAKING:
			dht->dhtPin=WAIT_RESPONSE_START;
			break;
		case WAIT_RESPONSE_START:
			dht->dhtPin=WAIT_RESPONSE_STOP;
			break;
		case WAIT_RESPONSE_STOP:
			dht->dhtPin=RECEIVING_BITS;
			break;
		case RECEIVING_BITS:
			counter = __HAL_TIM_GET_COUNTER(&htim1);
			if(counter<=100)
			{
				dht_byte&= ~(1<<(7-p));
			}
			else dht_byte|= (1<<(7-p));

			p++;
			dht->bitcount++;

			if(dht->bitcount%8==0){
				DHT_data[m]=dht_byte;
				dht_byte=0;
				m++;
				p=0;
			}

			if(dht->bitcount>=40){
				dht->bitcount=0;
				m=0;

				dht->dhtPin=DATA_RECEIVED;
			}
			break;
		case DATA_RECEIVED:
			break;
		}
		__HAL_TIM_SET_COUNTER(&htim1, 0);
	}
}

int Dht_hasData(DHT* dht){
	if (dht->dhtPin==DATA_RECEIVED){
		startdelay=0;
		delay =0;
		dht->dhtPin=WAKING;
		return 1;
	}
	return 0;
}


void DHT_onTimerInteruppt(DHT* dht){
 if(startdelay==1){
	if (dht_count>=18){
		delay=1;
		dht_count=0;
	}
		dht_count++;
 }
}















































