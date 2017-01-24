/**
  ******************************************************************************
  * File Name          : get_readings.c
  * Description        : Implements logic for sampling sensor data
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "get_readings.h"

/* Global declarations */
typedef struct stateInfo{
	float q, r, x, p, k;
}kalman_state;
kalman_state x_kstate, y_kstate, z_kstate, temp_kstate;

/* Function prototypes */
void Kalmanfilter_init(void);
int Kalmanfilter_C(float measured_acceleration, kalman_state* kstate);

/**
	 * @brief Main logic to sample readings from accelerometer and temperature sensor
	 * and do post processing including treating values by Kalman filter and calculate
	 * pitch and roll readings
	 * @param void
   * @retval void
   */
void get_readings(void){
	// printf("mems: now interrupt = %d\n\r", interrupt);
	LIS3DSH_ReadACC(read_acc);	
	// printf("%f | %f | %f\n", read_acc[0], read_acc[1], read_acc[2]);
	
	output_x = read_acc[0];
	output_y = read_acc[1];
	output_z = read_acc[2];
	
	Kalmanfilter_C(output_x, &x_kstate);
	Kalmanfilter_C(output_y, &y_kstate);
	Kalmanfilter_C(output_z, &z_kstate);
	
	//Save the filtered Ax, Ay, Az values
	output_x = x_kstate.x;
	output_y = y_kstate.x;
	output_z = z_kstate.x;

	roll  = (atan2(-output_y, output_z) * 180.0) / 3.1416;
	// printf("roll= %f | ", roll);
	txBuffer[0] = roll;

	pitch = (atan2(output_x, sqrt(output_y * output_y + output_z * output_z))*180.0) / 3.1416;
	// printf("pitch= %f\n", pitch);
	txBuffer[1] = pitch;	

	if(HAL_ADC_Start(&ADC1_Handle) != HAL_OK) printf("Couldn't start ADC\n");
	if(HAL_ADC_PollForConversion(&ADC1_Handle, 1000000) == HAL_OK){				
		temp = HAL_ADC_GetValue(&ADC1_Handle);		
		Kalmanfilter_C(temp, &temp_kstate);
		temp = temp_kstate.x;
		out_temp = (temp * 3000) / 4096;
		out_temp = ((out_temp - 760) / (double) 2.5) + 25;
		// printf("temperature= %f\n", out_temp);
		txBuffer[2] = out_temp;
	}
	else printf("Poll for conversion not working!\n");
}

/**
   * @brief A function used to filter the noisy acceleration readings
	 * @param 
   * @param kstate: pointer to the kalman filter configuration struct
	 * @retval 
   */
int Kalmanfilter_C(float measured_acceleration, kalman_state* kstate) {	
	kstate->p = kstate->p + kstate->q;
	kstate->k = kstate->p / (kstate->p + kstate->r);
	kstate->x = kstate->x + kstate->k * (measured_acceleration-kstate->x);

	//The following conditional checks if kstate->x is not a number
	if (kstate->x != kstate->x) {
		printf("An error has occured -NaN value was found"); 
		return 1;
	}
	
	kstate->p = (1-kstate->k) * kstate->p;
	return 0; 
}

/**
   * @brief A function used to initialize the kalman filter struct for all kalman state objects
	 * @param	none
	 * @retval none
   */
void Kalmanfilter_init(void) {
	
	//Kalman state struct to filter Ax values
	x_kstate.q = 0.10f; //process noise covariance
	x_kstate.r = 2.00f; //measurement noise covariance
	x_kstate.x = 0.0f; //estimated value
	x_kstate.p = 2.0f; //estimation error covariance
	x_kstate.k = 0.0f; //kalman gain
	
	//Kalman state struct to filter Ay values
	y_kstate.q = 0.10f; //process noise covariance
	y_kstate.r = 2.00f; //measurement noise covariance
	y_kstate.x = 0.0f; //estimated value
	y_kstate.p = 2.0f; //estimation error covariance
	y_kstate.k = 0.0f; //kalman gain
	
	//Kalman state struct to filter Az values
	z_kstate.q = 0.10f; //process noise covariance
	z_kstate.r = 2.00f; //measurement noise covariance
	z_kstate.x = 1000.0f; //estimated value
	z_kstate.p = 2.0f; //estimation error covariance
	z_kstate.k = 0.0f; //kalman gain
	
	//Kalman state struct to filter Temp values
	temp_kstate.q = 0.02f; //process noise covariance
	temp_kstate.r = 0.5f; //measurement noise covariance
	temp_kstate.x = 1048.0f; //estimated value
	temp_kstate.p = 2.0f; //estimation error covariance
	temp_kstate.k = 0.00f; //kalman gain
}

