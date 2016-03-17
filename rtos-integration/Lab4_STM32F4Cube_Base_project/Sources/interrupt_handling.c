#include "interrupt_handling.h"

void EXTI0_IRQHandler(void){
	
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

}

void TIM3_IRQHandler(void){
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

}