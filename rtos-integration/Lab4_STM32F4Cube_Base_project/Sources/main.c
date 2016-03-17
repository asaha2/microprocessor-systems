/*******************************************************************************
  * @file    main.c
  * @author  Ashraf Suyyagh
	* @version V1.2.0
  * @date    17-January-2016
  * @brief   This file demonstrates flasing one LED at an interval of one second
	*          RTX based using CMSIS-RTOS 
  ******************************************************************************
  */

#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "RTE_Components.h"             // Component selection
#include <stdio.h>
#include "system_config.h"
// #include "supporting_functions.h"

/* extern void initializeLED_IO			(void);
extern void start_Thread_LED			(void);
extern void Thread_LED(void const *argument);
extern osThreadId tid_Thread_LED; */

extern int start_Thread_ADC(void);
extern void Thread_ADC(void const *argument);
extern ADC_HandleTypeDef ADC1_Handle;

/**
	These lines are mandatory to make CMSIS-RTOS RTX work with te new Cube HAL
*/
#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void) { 
  return os_time; 
}
#endif

/**
  * Main function
  */
int main (void) {

  osKernelInitialize();

  HAL_Init();

  SystemClock_Config();
	ADC_Config();

	/* User codes goes here*/
  // initializeLED_IO();                       /* Initialize LED GPIO Buttons    */
  // start_Thread_LED();                       /* Create LED thread              */
	
	start_Thread_ADC();	
	/* User codes ends here*/
  
	osKernelStart();
}
