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

/* extern void initializeLED_IO			(void);
extern void start_Thread_LED			(void);
extern void Thread_LED(void const *argument);
extern osThreadId tid_Thread_LED; */

void TextOut(const char *str);
int fputc(int ch, FILE *f);

extern int start_Thread_ADC(void);
// extern void Thread_ADC(void const *argument);
// extern ADC_HandleTypeDef ADC1_Handle;

extern int start_Thread_DISP(void);
// extern void Thread_DISP(void const *argument);

osMutexDef(temp_mutex);
osMutexId(temp_mutex_id);

/**
	These lines are mandatory to make CMSIS-RTOS RTX work with te new Cube HAL
*/
#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;

uint32_t HAL_GetTick(void){ 
	
  return os_time; 
}
#endif

/**
  * Main function
  */
int main(void){

  osKernelInitialize();

  HAL_Init();
  SystemClock_Config();
	ADC_Config();
	GPIO_Config();
	
	temp_mutex_id = osMutexCreate(osMutex(temp_mutex));

	/* User codes goes here*/
  // initializeLED_IO();                       /* Initialize LED GPIO Buttons    */
  // start_Thread_LED();                       /* Create LED thread              */
	
	start_Thread_ADC();	
	start_Thread_DISP();
	/* User codes ends here*/
  
	osKernelStart();
}

void TextOut(const char *str){
  do{
    if(*str=='\n') ITM_SendChar('\r');
    ITM_SendChar(*str);
  } while(*str++);
}

int fputc(int ch, FILE *f){
	return ITM_SendChar(ch);
}
	
