#ifndef INC_MYMAIN_H_
#define INC_MYMAIN_H_
#include "mybuzzer.h"
#include "new_button.h"
#include "LED.h"
#include "main.h"
#include "clock.h"
extern UART_HandleTypeDef huart2;

int commTask();
void handleCommand();
int _write(int fd, char* ptr, int len);
LED_STATE UPDATE(LED *led, int max);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//		if(buzzer == 0 ){
//			HAL_TIM_Base_Start(&htim3);
//			HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//			buzzer = 1;
//		}
//		else {
//			HAL_TIM_Base_Stop(&htim3);
//			HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//			buzzer = 0;
//		}
//	}


#endif /* INC_MYMAIN_H_ */
