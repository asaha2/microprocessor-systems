/*******************************************************************************
  * @file    main.c
  * @author  Ashraf Suyyagh
	* @version V1.2.0
  * @date    17-January-2016
  * @brief   This file demonstrates flasing one LED at an interval of one second
	*          RTX based using CMSIS-RTOS 
  ******************************************************************************
  */

#include "stm32f4xx_hal.h"
#include "cmsis_os.h"
#include "RTE_Components.h"
#include <stdio.h>
#include "system_config.h"

int fputc(int ch, FILE *f);
extern int start_Thread_ADC(void);
extern int start_Thread_DISP(void);
extern int start_Thread_MEMS(void);

osMutexDef(temp_mutex);
osMutexId(temp_mutex_id);

osMutexDef(mems_mutex);
osMutexId(mems_mutex_id);

/**
	These lines are mandatory to make CMSIS-RTOS RTX work with te new Cube HAL
*/
#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void){ 
	
  return os_time; 
}
#endif

int main(void){

  osKernelInitialize();

  HAL_Init();
  SystemClock_Config();
	ADC_Config();
	GPIO_Config();
	MEMS_Config();
	MEMS_Config_IT();
	TIM3_Config();
	
	temp_mutex_id = osMutexCreate(osMutex(temp_mutex));
	mems_mutex_id = osMutexCreate(osMutex(mems_mutex));
	
	start_Thread_ADC();	
	start_Thread_DISP();
	
	start_Thread_MEMS();
	
	osKernelStart();
}

int fputc(int ch, FILE *f){
	return ITM_SendChar(ch);
}
	
