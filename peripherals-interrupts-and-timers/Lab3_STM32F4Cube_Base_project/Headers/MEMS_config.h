#include "stdint.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "lis3dsh.h"

extern LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
extern LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_InterruptConfigStruct;
extern GPIO_InitTypeDef GPIOE_Init;

void MEMS_Init(void);
void MEMS_Start_IT(void);

