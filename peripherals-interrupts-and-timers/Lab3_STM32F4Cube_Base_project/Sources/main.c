/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program subroutine
	* Author						 : Ashraf Suyyagh
	* Version            : 1.0.0
	* Date							 : January 14th, 2016
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "supporting_functions.h"
#include "lis3dsh.h"
#include "math.h"
#include "kalman_filter.h"
#include "sys_config.h"
#include "MEMS_config.h"
#include "7seg_display.h"

LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_InterruptConfigStruct;
GPIO_InitTypeDef GPIOE_Init;
TIM_Base_InitTypeDef TIM_Base_InitStruct;
TIM_HandleTypeDef TIM_HandleStruct;

int interrupt, interrupt_2;
int counter;

/* Private function prototypes -----------------------------------------------*/

int main(void){	
			
	float read_acc[] = {0, 0, 0};
	
	float output_x[] = {0};
	float output_y[] = {0};
	float output_z[] = {0};
	
	int parsed[] = {0, 0, 0, 0};
	
	kalman_state kstate_x;
	kalman_state kstate_y;
	kalman_state kstate_z;
	
	float den_pitch, den_roll;
	float pitch, roll;
	
	/* MCU Configuration */
  HAL_Init();

  /* Configure the system clock, peripherals and timers */
  SystemClock_Config();
	MEMS_Init();
	MEMS_Start_IT();
	TIM3_Config();	
	
	Reset(&kstate_x);	
	Reset(&kstate_y);
	Reset(&kstate_z);
	
	counter = 0;
	interrupt = 0;
	
	while (1){
						
		// printf("main: counter = %d, interrupt = %d\n", counter, interrupt);
		if(interrupt != 0){
			interrupt = 0;
			// printf("main: counter = %d, interrupt = %d\n", counter, interrupt);
			
			LIS3DSH_ReadACC(read_acc);	
			// printf("%f | %f | %f\n", read_acc[0], read_acc[1], read_acc[2]);
			
			if(!Kalmanfilter_C(read_acc[0], output_x, &kstate_x) && !Kalmanfilter_C(read_acc[1], output_y, &kstate_y) 
				&& !Kalmanfilter_C(read_acc[2], output_z, &kstate_z)){				
					
					// printf("%f | %f | %f\n", output_x[0], output_y[0], output_z[0]);
					den_pitch = sqrt(pow(output_y[0], 2) + pow(output_z[0], 2));
					den_roll 	= sqrt(pow(output_x[0], 2) + pow(output_z[0], 2));
					pitch = atan(output_x[0] / den_pitch) * (180 / 3.1416);
					roll = atan(output_y[0] / den_roll) * (180 / 3.1416);
					// printf("%f | %f\n", pitch, roll);
					// printf("%f\n", roll);
					Parse(parsed, roll);
					// printf("%d %d %d %d\n", parsed[3], parsed[2], parsed[1], parsed[0]);
			}
		}
	}
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line){
}
#endif

