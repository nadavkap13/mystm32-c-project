#ifndef INC_DHA_11_H_
#define INC_DHA_11_H_
#include "main.h"
#include <stdint.h>


typedef enum  {
	WAKING,
	WAIT_RESPONSE_START,
	WAIT_RESPONSE_STOP,
	RECEIVING_BITS,
	DATA_RECEIVED
}DHT_STATE;

typedef struct _DHT{
	DHT_STATE dhtPin;
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	int bitcount;



}DHT;

void DHT_Init(DHT* dht,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
int DHTRead();
int DHTResponse();
//static void setGpioExti(DHT* dht);
void Dht_readAsync(DHT* dht);
void Dht_onGpioInterrupt(DHT* dht, uint16_t pin);
int Dht_hasData(DHT* dht);
void DHT_onTimerInteruppt(DHT* dht);


#endif /* INC_DHA_11_H_ */
