#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "supporting_functions.h"
#include "LIS3DSH.h"

extern ADC_HandleTypeDef ADC1_Handle;

void SystemClock_Config(void);
void ADC_Config(void);
void GPIO_Config(void);
void MEMS_Config(void);
void MEMS_Config_IT(void);
void TIM3_Config(void);
