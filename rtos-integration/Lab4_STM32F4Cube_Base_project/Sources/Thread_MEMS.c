#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "LIS3DSH.h"

void Thread_MEMS(void const *argument);
osThreadId tid_Thread_MEMS;
osThreadDef(Thread_MEMS, osPriorityNormal, 1, 0);

TIM_HandleTypeDef TIM_HandleStruct;

extern int interrupt;

int start_Thread_MEMS(void){

  tid_Thread_MEMS = osThreadCreate(osThread(Thread_MEMS), NULL);
  if (!tid_Thread_MEMS) return(-1); 
  return(0);
}

void Thread_MEMS(void const *argument){
	
	float read_acc[] = {0, 0, 0};
	while(1){
		osDelay(1000);
		// printf("mems: works\n\r");
		printf("mems: interrupt = %d\n\r", interrupt);
		if(interrupt != 0){
			printf("mems: now interrupt = %d\n\r", interrupt);
			interrupt = 0;
			LIS3DSH_ReadACC(read_acc);	
			printf("%f | %f | %f\n", read_acc[0], read_acc[1], read_acc[2]);
		}
	}
}


	
