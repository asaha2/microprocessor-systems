#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "7seg_display.h"

void Thread_DISP(void const *argument);
osThreadId tid_Thread_DISP;
osThreadDef(Thread_DISP, osPriorityNormal, 1, 0);

extern osMutexId temp_mutex_id;
extern double output;

int start_Thread_DISP(void){

  tid_Thread_DISP = osThreadCreate(osThread(Thread_DISP), NULL); // Start LED_Thread
  if (!tid_Thread_DISP) return(-1); 
  return(0);
}

void Thread_DISP(void const *argument){
	
	double temp2;
	int disp[] = {0, 0, 0, 0}; 
	int* temp3;
	int counter = 1;
	int counter2 = 0;
	
	while(1){
		// osDelay(10);
		osMutexWait(temp_mutex_id, osWaitForever);
		temp2 = output;
		osMutexRelease(temp_mutex_id);
		// printf("disp: temp2= %f\n", temp2);		
		Parse_Temp(temp2, disp);
		// printf("%d %d %d %d\n", disp[3], disp[2], disp[1], disp[0]);
		
		if(counter == 1){
			temp3 = disp;
		}
		
		if(counter2 <= 2){
			if(temp3[3] == 3 && temp3[2] > 6 && counter > 100);
			else Display(temp3[3], 4);
		}
		
		else if(counter2 <= 4){
			if(temp3[3] == 3 && temp3[2] > 6 && counter > 100);
			else Display(temp3[2], 3);
		}
		
		else if(counter2 <= 6){
			if(temp3[3] == 3 && temp3[2] > 6 && counter > 100);
			else Display(temp3[0], 1);
		}
		
		else{
			if(temp3[3] == 3 && temp3[2] > 6 && counter > 100);
			else Display(temp3[1], 2);
		}

		/* Reset loop counter after 90 cycles */
		if(counter > 1200){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			counter = 0;					
		}
		
		/* Reset loop counter after 4 cycles */
		if(counter2 > 6){
			counter2 = 0;
		}
		
		counter++;
		counter2++;
	}
}
	

