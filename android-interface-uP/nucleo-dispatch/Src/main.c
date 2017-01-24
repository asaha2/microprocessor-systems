/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main thread implementation
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "cube_hal.h"
#include "osal.h"
#include "sensor_service.h"
#include "debug.h"
#include "stm32_bluenrg_ble.h"
#include "bluenrg_utils.h"
#include "SPI_Config.h"
#include <string.h>
#include <stdio.h>
 
/* Global declarations */
SPI_HandleTypeDef SpiHandle_2;
SPI_HandleTypeDef SpiHandle_3;
uint8_t txBuffer = 5;

/* Extern declarations */
extern void SPI_SendData(SPI_HandleTypeDef *hspi, uint16_t Data);
extern uint8_t SPI_ReceiveData(SPI_HandleTypeDef *hspi);

/**
	 * @brief Main thread superloop implementation to sample SPI data transmitted and
	 * subsequently display on the local serial debugger
	 * @param void
   * @retval int
   */

int main(void){
	
	uint8_t rxBuffer[4]= {0, 0, 0, 0};
//	int i, count;
	extern volatile uint8_t button_event;
	
	/* INITIALIZE SYSTEM CLOCK AND SPI PERIPHERAL */
  HAL_Init();  
  SystemClock_Config();
	SPI_Init1();
	// SPI_Init2();
	
	/* BEGIN MAIN SUPERLOOP */
  while(1){
		
		/* READ DATA TRANSMITTED OVER SPI BUS */
		SPI_Read(rxBuffer, 4);		
		printf("roll = %u | pitch = %u | temp = %u\n", rxBuffer[0], rxBuffer[1], rxBuffer[2]);
		rxBuffer[0] = 0;
		rxBuffer[1] = 0;
		rxBuffer[2] = 0;
		
//		for(i = 0; i < 3; i++){
//			printf("%u ", rxBuffer[i]);
//			rxBuffer[i] = 0;
//		}
//		printf("\n");
  }
}

