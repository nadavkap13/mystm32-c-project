#include "comtask.h"
#include "mymain.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER_LENGTH 100
extern Function arry[100];
uint8_t cmdbuffer[MAX_BUFFER_LENGTH];
int cmdcount = 0;
int cmdprint = 0;
int funcounter = 0;

void RegisterCommand(char *CommandName, HandlerFunc Func, void *obj) {
	arry[funcounter].Func = Func;
	arry[funcounter].CommandName = CommandName;
	arry[funcounter].obj = obj;
	funcounter++;
}

void RegisterCallbacks(HandlerFunc onFunc, HandlerFunc offFunc, void * object){
//	On = onFunc;
//	Off = offFunc;
//	type = object;
}

int commTask() {
	uint8_t ch;

	HAL_StatusTypeDef Status = HAL_UART_Receive(&huart2, &ch, 1, 10);
	if (Status != HAL_OK) {
		if ((huart2.Instance->ISR & USART_ISR_ORE) != 0) {
			__HAL_UART_CLEAR_OREFLAG(&huart2);
		}

		// here we have a time to print the command
		while (cmdprint < cmdcount) {
			HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
		}

		return 0;
	}

	if (ch != '\r' && ch != '\n') {
		//HAL_UART_Transmit(&huart2, &ch, 1, 0xFFFF);

		if (cmdcount >= MAX_BUFFER_LENGTH) {
			cmdcount = 0;
			cmdprint = 0;
		}

		cmdbuffer[cmdcount++] = ch;
		return 0;
	}

	// here we have a time to print the command
	while (cmdprint < cmdcount) {
		HAL_UART_Transmit(&huart2, &cmdbuffer[cmdprint++], 1, 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*) "\r\n", 2, 0xFFFF);

	cmdbuffer[cmdcount] = 0;
	cmdcount = 0;
	cmdprint = 0;
	return 1;
}

void handleCommand() {
	char cmd[20];
	char param[20];


	int params = sscanf((const char*) cmdbuffer, "%s %s", cmd, param);

	for (int j = 0; j < funcounter; j++) {
		if (strcmp(cmd, arry[j].CommandName) == 0) {
			arry[j].Func(arry[j].obj, param);
			return;
		}
	}

	if (params == 0) {
		return;
	}

//  if (strcmp(cmd, "startled") == 0)
//  {
//	 On(type);
//  }
//  else if (strcmp(cmd, "stopled") == 0)
//  {
//	  Off(type);
//  }
//  else if (strcmp(cmd, "ledblink") == 0)
//   {
//	 ledBlink(&ledred, maxCount);
//	 ledBlink(&ledblue, maxCount);
//   }
//  else if (strcmp(cmd, "setled") == 0)
//   {
//	  HAL_TIM_Base_Start_IT(&htim4);
//	  ledsetbrightness(&ledred,maxCount);
//
//	  //ledsetbrightness(&ledblue,maxCount);
//   }
//  else if (strcmp(cmd, "gettick") == 0)
//    {
// 	  getClockTick(&clock, &tick);
// 	  printf("tick is %u\n\r", tick);
//    }
//  else if (strcmp(cmd, "gettime") == 0)
//    {
// 	  getTime(&clock, &sec, &min, &hour);
//	  printf("time is %zu,%zu,%zu\n\r", hour, min, sec);
//    }
//
//  else if (strcmp(cmd, "startbuzzer") == 0)
//   {
//	  buzzerStartPlay(&buzz, song, length);
//   }
//  else if (strcmp(cmd, "stopbuzzer") == 0)
//   {
//	  buzzerStopPlay();
//   }
	else {
		printf("Invalid command\r\n");
	}
}
