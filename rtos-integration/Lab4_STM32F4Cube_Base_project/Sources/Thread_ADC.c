#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

void Thread_ADC (void const *argument);
void TextOut(const char *str);
osThreadId tid_Thread_ADC;
osThreadDef(Thread_ADC, osPriorityNormal, 1, 0);
// GPIO_InitTypeDef LED_configuration;

ADC_HandleTypeDef ADC1_Handle;

int start_Thread_ADC(void){

  tid_Thread_ADC = osThreadCreate(osThread(Thread_ADC), NULL); // Start LED_Thread
  if (!tid_Thread_ADC){
		TextOut("Error\n");
		return(-1); 
	}
  return(0);
}

void Thread_ADC(void const *argument){
	double temp;
	while(1){
		osDelay(1000);
		// HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		HAL_ADC_Start(&ADC1_Handle);
		// TextOut("Polling for conversion...\n\r");
		if(HAL_ADC_PollForConversion(&ADC1_Handle, 1000000) == HAL_OK){
			temp = HAL_ADC_GetValue(&ADC1_Handle);
			if(temp > 1000 && temp < 2000) TextOut("Working!\n");
			else TextOut("Less than 1000\n");
		}
		else TextOut("Poll for conversion not working!\n");
	}
}
	
void TextOut(const char *str){
	do{
		if(*str=='\n') ITM_SendChar('\r');
		ITM_SendChar(*str);
	} while(*str++);
}
	




