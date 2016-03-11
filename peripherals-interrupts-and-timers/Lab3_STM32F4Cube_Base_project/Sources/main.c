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
#include "sys_config.h"
#include "MEMS_config.h"
#include "7seg_display.h"
#include "gpio_config.h"
#include "keypad.h"
#include "get_readings.h"

void arm_abs_f32(float32_t *pSrc, float32_t *pDst, uint32_t blockSize);

LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_InterruptConfigStruct;
GPIO_InitTypeDef GPIOE_Init;
TIM_Base_InitTypeDef TIM_Base_InitStruct;
TIM_HandleTypeDef TIM_HandleStruct;

GPIO_InitTypeDef GPIOA_Init;						
GPIO_InitTypeDef GPIOE_Init;						
GPIO_InitTypeDef GPIOD_Init;
GPIO_InitTypeDef GPIOC_Init;
GPIO_InitTypeDef GPIOB_Init;

volatile int interrupt, interrupt_2, interrupt_3, interrupt_4, interrupt_5;
int counter;

float read_acc[] = {0, 0, 0};
int parsed[] = {0, 0, 0, 0, 0};
int displaying[] = {0, 0, 0, 0, 0};

int sample_col, sample_row;
int temp_col, temp_row;

float output_x[] = {0};
float output_y[] = {0};
float output_z[] = {0};

kalman_state kstate_x;
kalman_state kstate_y;
kalman_state kstate_z;

float den_pitch, den_roll;
float pitch, roll;

float diff_in, diff_out;

int main(void){	
	
	/* char char_1 = '\0';
	char char_2 = '\0';
	char char_3 = '\0';
	char char_4 = '\0';
	
	int lock = 0; */
			
	/* MCU Configuration */
  HAL_Init();

  /* Configure the system clock, peripherals and timers */
  SystemClock_Config();
	MEMS_Init();
	MEMS_Start_IT();
	TIM3_Config();	
	GPIO_Config();
	
	Reset(&kstate_x);	
	Reset(&kstate_y);
	Reset(&kstate_z);
	
	counter = 0;
	interrupt = 0;	
	
	while (1){
		
		Get_Sensor_Data(30.0);
		
		// if((roll - alarm) <= 4)Display_Alarm();
		// Reset_Alarm();
		
		
//		sample_col = Get_Column();
//		sample_row = Get_Row();
//		if(sample_col != NULL && sample_row != NULL && lock == 0 && char_1 == '\0'){
//			char_1 = Get_Key();
//			printf("char_1 = %c entered\n", char_1);
//			lock = 1;
//		}
//		
//		if(char_1 != '#'){			
//			sample_col = Get_Column();
//			sample_row = Get_Row();
//			if((char_1 == '0' || char_1 == '1' || char_1 == '2' || char_1 == '3' || char_1 == '4' || char_1 == '5' || char_1 == '6' ||
//					char_1 == '7' || char_1 == '8' || char_1 == '9' || char_1 == '#') && sample_col != NULL && sample_row != NULL && char_2 == '\0'){
//				char_2 = Get_Key();
//				printf("char_2 = %c entered\n", char_2);
//			}
//		}else{
//			lock = 0;
//		}
//		
//		if(char_2 != '#'){
//			sample_col = Get_Column();
//			sample_row = Get_Row();
//			if((char_2 == '0' || char_2 == '1' || char_2 == '2' || char_2 == '3' || char_2 == '4' || char_2 == '5' || char_2 == '6' ||
//					char_2 == '7' || char_2 == '8' || char_2 == '9' || char_2 == '#') && sample_col != NULL && sample_row != NULL && char_3 == '\0'){
//				char_3 = Get_Key();
//				printf("char_3 = %c entered\n", char_3);
//			}
//		}else{
//			Get_Sensor_Data();
//		}
//		
//		if(char_3 != '#'){
//			sample_col = Get_Column();
//			sample_row = Get_Row();
//			if((char_3 == '0' || char_3 == '1' || char_3 == '2' || char_3 == '3' || char_3 == '4' || char_3 == '5' || char_3 == '6' ||
//					char_3 == '7' || char_3 == '8' || char_3 == '9' || char_3 == '#') && sample_col != NULL && sample_row != NULL && char_4 == '\0'){
//				char_4 = Get_Key();
//				printf("char_4 = %c entered\n", char_4);
//			}
//		}else{
//			Get_Sensor_Data();
//		}
//		
//		if(char_4 != '#'){
//			lock = 0;
//			char_1 = '\0';
//			char_2 = '\0';
//			char_3 = '\0';
//			char_4 = '\0';
//		}else{
//			Get_Sensor_Data();
//		} 
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

