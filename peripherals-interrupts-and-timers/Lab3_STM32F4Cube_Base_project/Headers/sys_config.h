#include "stdint.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"

extern TIM_Base_InitTypeDef TIM_Base_InitStruct;
extern TIM_HandleTypeDef TIM_HandleStruct;

void SystemClock_Config	(void);
void TIM3_Config(void);
