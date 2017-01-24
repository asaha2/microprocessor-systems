/**
  ******************************************************************************
  * File Name          : pwm_display.h
  * Description        : Associated header file for 'pwm_display.c'
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "stm32f4xx_hal.h"

/* Extern declarations */
extern int counter, pwm, speed, orient;
extern uint8_t rxBuffer;
extern TIM_OC_InitTypeDef TIM_OCStruct;
extern TIM_HandleTypeDef TIM_HandleStruct2;

/* Function prototypes */
void pwm_display(void);

