/**
  ******************************************************************************
  * File Name          : get_readings.h
  * Description        : Associated header file for 'get_readings.c'
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "LIS3DSH.h"
#include "math.h"

/* Extern declarations */
extern float read_acc[3];
extern float output_x, output_y, output_z;
extern float pitch, roll;
extern uint8_t txBuffer[4];
extern float temp, out_temp;
extern ADC_HandleTypeDef ADC1_Handle;

/* Function prototypes */
void get_readings(void);
