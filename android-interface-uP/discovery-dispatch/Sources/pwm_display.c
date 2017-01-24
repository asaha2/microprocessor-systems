/**
  ******************************************************************************
  * File Name          : pwm_display.c
  * Description        : Implements main logic PWM display LEDs
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "pwm_display.h"

/**
	 * @brief Implements the main logic to toggle the rotation order and the brightness
	 * of the LED display using the Pulse Width Modulation method
	 * @param void
   * @retval void
   */
void pwm_display(void){
	
		pwm = rxBuffer;		
		// printf("rxBuffer = %u, pwm = %u\n", rxBuffer, pwm);

	/* PWM CLOCKWISE */
		if(orient % 2 == 0)
		{		
			TIM_OCStruct.OCMode = TIM_OCMODE_PWM1;
			TIM_OCStruct.Pulse = pwm;
			TIM_OCStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
			
			if(HAL_TIM_OC_Init(&TIM_HandleStruct2) != HAL_OK) printf("Error initializing OC\n");
			if(HAL_TIM_PWM_Init(&TIM_HandleStruct2) != HAL_OK) printf("Error initializing PWM\n");
			
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_1) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_2) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_3) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_4) != HAL_OK) printf("Error configuring OC\n");
			
			if(counter <= speed){
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_1) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_1 != HAL_OK)) printf("Error starting PWM\n");
			}		
			else if(counter > speed && counter <= (speed * 2)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_2) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_2 != HAL_OK)) printf("Error starting PWM\n");
			}
			else if(counter > (speed * 2) && counter <= (speed * 3)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_2) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_2 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_3) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_3 != HAL_OK)) printf("Error starting PWM\n");
			}
			else{
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_3) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_3 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_4) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_4 != HAL_OK)) printf("Error starting PWM\n");
			}
			
			counter++;
			if(counter > (speed * 4)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_4) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_4 != HAL_OK)) printf("Error starting PWM\n");
				counter = 0;				
			}
		}
		
		/* PWM ANTICLOCKWISE */
		else
		{			
			TIM_OCStruct.OCMode = TIM_OCMODE_PWM1;
			TIM_OCStruct.Pulse = pwm;
			TIM_OCStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
			
			if(HAL_TIM_OC_Init(&TIM_HandleStruct2) != HAL_OK) printf("Error initializing OC\n");
			if(HAL_TIM_PWM_Init(&TIM_HandleStruct2) != HAL_OK) printf("Error initializing PWM\n");
			
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_1) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_2) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_3) != HAL_OK) printf("Error configuring OC\n");
			if(HAL_TIM_OC_ConfigChannel(&TIM_HandleStruct2, &TIM_OCStruct, TIM_CHANNEL_4) != HAL_OK) printf("Error configuring OC\n");
						
			if(counter <= speed){
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_4) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_4 != HAL_OK)) printf("Error starting PWM\n");				
			}		
			else if(counter > speed && counter <= (speed * 2)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_4) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_4 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_3) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_3 != HAL_OK)) printf("Error starting PWM\n");
				
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1 != HAL_OK)) printf("Error starting PWM\n");
			}
			else if(counter > (speed * 2) && counter <= (speed * 3)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_3) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_3 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_2) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_2 != HAL_OK)) printf("Error starting PWM\n");				
			}
			else{
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_2) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_2 != HAL_OK)) printf("Error starting PWM\n");
				if(HAL_TIM_OC_Start(&TIM_HandleStruct2, TIM_CHANNEL_1) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Start(&TIM_HandleStruct2, TIM_CHANNEL_1 != HAL_OK)) printf("Error starting PWM\n");
			}
			
			counter++;
			if(counter > (speed * 4)){
				if(HAL_TIM_OC_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1) != HAL_OK) printf("Error starting OC\n");				
				if(HAL_TIM_PWM_Stop(&TIM_HandleStruct2, TIM_CHANNEL_1 != HAL_OK)) printf("Error starting PWM\n");
				counter = 0;
			}
		}			
}

