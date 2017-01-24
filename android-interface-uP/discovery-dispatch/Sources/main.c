/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : The main thread of computation running in superloop
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */
	
/* Includes */
#include "supporting_functions.h"
#include "lis3dsh.h"
#include "SPI_Config.h"
#include "system_config.h"
#include "get_readings.h"
#include "pwm_display.h"
#include "double_tap.h"

#define LED_SPEED_MEDIUM

/* Global declarations */
SPI_HandleTypeDef SpiHandle_2;
SPI_HandleTypeDef SpiHandle_3;
ADC_HandleTypeDef ADC1_Handle;
GPIO_InitTypeDef GPIOD_Init2;
TIM_OC_InitTypeDef TIM_OCStruct;
TIM_HandleTypeDef TIM_HandleStruct2;
float read_acc[3] = {0, 0, 0};
float output_x, output_y, output_z;
float temp, out_temp;
float pitch, roll;
int counter, pwm, speed, orient;
float thresh1;
int assert1, assert2, assertFall, assertRise2, assertDoubleTap, counter2;

/* Extern declarations */
extern int interrupt;

uint8_t rxBuffer = 5;
uint8_t txBuffer[4] = {0, 0, 0, 0};

/**
	 * @brief Main thread of computation running in superloop to update sensor data and transmit
	 * and also subsequently run logic for PWM LED display and double tap detection
	 * @param void
   */
int main(void){	
		
	/* INITIALIZE SYSTEM CLOCK AND PERIPHERALS */
  HAL_Init();
  SystemClock_Config();	
	SPI_Init1();
	MEMS_Config();
	MEMS_Config_IT();
	ADC_Config();
	LED_Config();
	PWM_Config();
	
	/* CONFIG FOR PWM */
	#ifdef LED_SPEED_SLOWER
		speed = 1500;
	#endif

	#ifdef LED_SPEED_SLOW
		speed = 1000;
	#endif

	#ifdef LED_SPEED_MEDIUM
		speed = 800;
	#endif

	#ifdef LED_SPEED_FAST
		speed = 400;
	#endif

	#ifdef LED_SPEED_FASTER
		speed = 200;
	#endif			
	
	#ifdef LED_ALL_ON
		speed = 100;
	#endif
	
	/* CONFIG FOR DOUBLE TAP */
	counter2 = 0;
	thresh1 = 1300;
	assert1 = 0;
	assert2 = 0;
	assertFall = 0;
	assertRise2 = 0;
	assertDoubleTap = 0;
	
	/* BEGIN SUPERLOOP */
	while(1){
		
		/* SET SAMPLING DELAY FOR SENSORS */
		if(interrupt != 0){
			interrupt = 0;
			get_readings();			
		}		
		
		/* TRANSMIT SENSOR DATA TO MASTER */
		HAL_SPI_Transmit(&SpiHandle_2, txBuffer, 4, 10000);				
		
		/* LOGIC FOR IMPLEMENTING PWM DISPLAY LED */
		pwm_display();		
		
		/* LOGIG FOR IMPLEMENTING DOUBLE TAP DETECTION */
		double_tap();
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

