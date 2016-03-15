/*******************************************************************************
  * @file    main.c
  * @author  Aditya Saha & Habib Ahmed (original template by Ashraf Suyyagh)
	* @version V1.2.0
  * @date    17-January-2016
  * @brief   This file demonstrates flasing one LED at an interval of one second
	*          RTX based using CMSIS-RTOS 
  ******************************************************************************
  */

/* Includes */
#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "RTE_Components.h"             // Component selection

#include "system_config.h"
#include "kalman_filter.h"

/* Extern declarations */
TIM_Base_InitTypeDef TIM_Base_InitStruct;
TIM_HandleTypeDef TIM_HandleStruct;
ADC_InitTypeDef ADC1_Init;							
ADC_ChannelConfTypeDef ADC1_Channel;
ADC_HandleTypeDef ADC1_Handle;
GPIO_InitTypeDef GPIOA_Init;						
GPIO_InitTypeDef GPIOE_Init;						
GPIO_InitTypeDef GPIOD_Init;

extern void initializeLED_IO			(void);
extern void start_Thread_LED			(void);
extern void Thread_LED(void const *argument);
extern osThreadId tid_Thread_LED;

/**
	These lines are mandatory to make CMSIS-RTOS RTX work with the new Cube HAL
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

  osKernelInitialize();                     /* initialize CMSIS-RTOS          */

  HAL_Init();                               /* Initialize the HAL Library     */

  SystemClock_Config();                     /* Configure the System Clock     */
	TIM3_Config();
	ADC_Config();
	
	/* User codes goes here*/
  initializeLED_IO();                       /* Initialize LED GPIO Buttons    */
  start_Thread_LED();                       /* Create LED thread              */
	/* User codes ends here*/
  
	osKernelStart();                          /* start thread execution         */
}
