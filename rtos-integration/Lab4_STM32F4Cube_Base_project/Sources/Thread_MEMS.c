#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

void Thread_MEMS(void const *argument);
osThreadId tid_Thread_MEMS;
osThreadDef(Thread_MEMS, osPriorityNormal, 1, 0);

int start_Thread_MEMS(void){

  tid_Thread_MEMS = osThreadCreate(osThread(Thread_MEMS), NULL); // Start LED_Thread
  if (!tid_Thread_MEMS) return(-1); 
  return(0);
}

void Thread_MEMS(void const *argument){
	
	while(1){
		osDelay(1000);
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		printf("works\n\r");
	}
}


	
