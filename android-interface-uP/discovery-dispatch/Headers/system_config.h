/**
  ******************************************************************************
  * File Name          : system_config.h
  * Description        : Associated header file for 'system_config.c'
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include "supporting_functions.h"
#include "LIS3DSH.h"
#include "stm32f4xx_hal_tim.h"

/* Extern declarations */
extern ADC_HandleTypeDef ADC1_Handle;
extern GPIO_InitTypeDef GPIOD_Init2;
extern TIM_HandleTypeDef TIM_HandleStruct2;

/* Function prototypes */
void MEMS_Config(void);
void MEMS_Config_IT(void);
void ADC_Config(void);
void LED_Config(void);
void PWM_Config(void);
void SystemClock_Config(void);


