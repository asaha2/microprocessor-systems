#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"

int interrupt = 0;
int interrupt2 = 0;
int interrupt3 = 0;
int interrupt4 = 0;
int interrupt5 = 0;
int interrupt6 = 0;
int interrupt7 = 0;

int count = 0;
int count2 = 0;

extern TIM_HandleTypeDef TIM_HandleStruct;

void EXTI0_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void TIM3_IRQHandler(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
