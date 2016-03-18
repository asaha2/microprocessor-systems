/**
  ******************************************************************************
  * File Name          : Thread_ADC.c
  * Description        : Worker thread source code for the temperature sensor
	* Author						 : Aditya Saha & Habib Ahmed
	* Version            : 1.0.0
	* Date							 : March 18th, 2016
  ******************************************************************************
  */

/* Includes */
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "kalman_filter.h"

/* Thread function prototypes */
void Thread_ADC (void const *argument);
osThreadId tid_Thread_ADC;
osThreadDef(Thread_ADC, osPriorityNormal, 1, 0);

/* Global declarations */
kalman_state kstate;
ADC_HandleTypeDef ADC1_Handle;
double output;

/* Extern declarations */
extern osMutexId temp_mutex_id;
extern int interrupt6;

/**
	 * @brief Uses OS primitives to spawn a thread and check status
	 * @param void
   * @retval integer value showing error/run status of the configuration operation
   */
int start_Thread_ADC(void){

  tid_Thread_ADC = osThreadCreate(osThread(Thread_ADC), NULL);
  if (!tid_Thread_ADC){
		printf("Error\n");
		return(-1); 
	}
  return(0);
}

/**
	 * @brief Worker thread main superloop that defines how the thread will poll and gather temperature values
	 * @param void*
   * @retval void
   */
void Thread_ADC(void const *argument){
	
	double temp;
	Reset(&kstate);
	while(1){
		osDelay(1000);
		if(interrupt6 != 0){
			interrupt6 = 0;
			HAL_ADC_Start(&ADC1_Handle);
			if(HAL_ADC_PollForConversion(&ADC1_Handle, 1000000) == HAL_OK){
				temp = HAL_ADC_GetValue(&ADC1_Handle);
				// printf("adc: temp= %f\n", temp);
				osMutexWait(temp_mutex_id, osWaitForever);
				output = (temp * 3000) / 4096;
				output = ((output - 760) / 2.5) + 25;
				osMutexRelease(temp_mutex_id);
				// printf("adc: output= %f\n", output);
			}
			else printf("Poll for conversion not working!\n");
		}
	}
}




