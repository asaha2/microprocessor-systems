#include "stdint.h"
#include <stdio.h>
#include "supporting_functions.h"
#include "stm32f4xx_hal.h"
#include "lis3dsh.h"

extern LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
extern LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_InterruptConfigStruct;
extern GPIO_InitTypeDef GPIOE_Init;
extern TIM_Base_InitTypeDef TIM_Base_InitStruct;
extern TIM_HandleTypeDef TIM_HandleStruct;

void SystemClock_Config	(void);
void MEMS_Config(void);
void MEMS_ITConfig(void);
void TIM3_Config(void);
