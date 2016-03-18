#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "kalman_filter.h"

void Thread_ADC (void const *argument);
osThreadId tid_Thread_ADC;
osThreadDef(Thread_ADC, osPriorityNormal, 1, 0);

kalman_state kstate;
ADC_HandleTypeDef ADC1_Handle;

extern osMutexId temp_mutex_id;
extern int interrupt6;
double output;

int start_Thread_ADC(void){

  tid_Thread_ADC = osThreadCreate(osThread(Thread_ADC), NULL);
  if (!tid_Thread_ADC){
		printf("Error\n");
		return(-1); 
	}
  return(0);
}

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




