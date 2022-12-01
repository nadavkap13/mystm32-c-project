#include "Flash.h"
#include "main.h"
#include "DHA_11.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char arry[64] = "sahar is the king of all";
#define MAX_LENGTH 64
static int flashindex = 0;
uint32_t adress = (0x08080000UL);
uint32_t pageerror = 0;
extern DHT dht;
extern uint8_t DHT_data[5];

void pageSelect (FLASH_EraseInitTypeDef * page)
{
	page->TypeErase = FLASH_TYPEERASE_PAGES;
	page->Banks = FLASH_BANK_2;
	page->Page = 256;
	page->NbPages = 1;
}

void pageErase()
{
	FLASH_EraseInitTypeDef page;
	pageSelect(&page);

	if (HAL_FLASHEx_Erase(&page, &pageerror) != HAL_OK) {
		printf("Erase failed\r\n");
	}
}

void pageProgram ()
{
	int flashindex = 0;

	for (int i = 0 ; i<8; i++)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, adress+flashindex, *(uint64_t*)(arry+flashindex)) != HAL_OK) {
			printf("Program failed\r\n");
			break;
		}
		flashindex+=sizeof(uint64_t);
	}

}

void eraseIT()
{
	FLASH_EraseInitTypeDef page;
	pageSelect(&page);
	HAL_FLASH_Unlock();

	if (HAL_FLASHEx_Erase_IT(&page) != HAL_OK) {
		printf("Erase failed\r\n");
	}

}
void programIT()
{
	if (flashindex <= MAX_LENGTH ){

		if (HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, adress+flashindex, *(uint64_t*)(arry+flashindex)) != HAL_OK) {
			printf("Program failed\r\n");
		}
			flashindex+=sizeof(uint64_t);
	}
}


void tempflasherase()
{
	FLASH_EraseInitTypeDef page;
		pageSelect(&page);
		HAL_FLASH_Unlock();

		if (HAL_FLASHEx_Erase_IT(&page) != HAL_OK) {
			printf("Erase failed\r\n");
		}

}
void tempflashprogram()
{
	if (flashindex <= 2048 ){
		Dht_readAsync(&dht);
		if(Dht_hasData(&dht)){
			if (HAL_FLASH_Program_IT(FLASH_TYPEPROGRAM_DOUBLEWORD, adress+flashindex, *(uint64_t*)(DHT_data[2])) != HAL_OK) {
			printf("Program failed\r\n");
			}
			flashindex+=sizeof(uint64_t);
		}
	}
}







































