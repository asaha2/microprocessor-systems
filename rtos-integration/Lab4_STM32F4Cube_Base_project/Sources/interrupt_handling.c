#include "interrupt_handling.h"

void EXTI0_IRQHandler(void){
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(count > 4){
		interrupt++;
		count = 0;
	}
	count++;
}

void TIM3_IRQHandler(void){
	
	HAL_TIM_IRQHandler(&TIM_HandleStruct);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	interrupt2++;
	interrupt3++;
}

