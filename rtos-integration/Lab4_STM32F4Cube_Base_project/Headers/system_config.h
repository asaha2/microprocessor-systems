#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "supporting_functions.h"
#include "LIS3DSH.h"
#include "stm32f4xx_hal_tim.h"

extern ADC_HandleTypeDef ADC1_Handle;
extern TIM_HandleTypeDef TIM_HandleStruct;

void SystemClock_Config(void);
void ADC_Config(void);
void GPIO_Config(void);
void MEMS_Config(void);
void MEMS_Config_IT(void);
void TIM3_Config(void);
