/**
  ******************************************************************************
  * File Name          : double_tap.c
  * Description        : Implements logic for double tap detection
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */

/* Includes */
#include "double_tap.h"
#include <stdio.h>

/**
	 * @brief Implements main logic for double tap detection. Once detected it simply
	 * prints an assertion message on the local serial debugger and resets configuration
	 * new double tap detection
	 * @param void
   * @retval void
   */
void double_tap(void){

	if(assert2 > 3){
		printf("detected\n");
	}		
	
	if(counter2 > 16000 && read_acc[2] > thresh1 && assert1 == 0 && assertFall == 0 && assertRise2 == 0){
		assert1 = 1;
		printf("rising edge 1 detected\n");
		counter2 = 0;
		assertDoubleTap = 0;
		// printf("%f\n", z_acc);
	}
	
	if(counter2 > 1000 && assert1 == 1 && read_acc[2] < thresh1 && assertFall == 0 && assertRise2 == 0) {
		assertFall = 1;
		assert1 = 0;
		counter2 = 0;
		printf("falling edge 1 detected\n");
	}
	
	if(counter2 > 4000 && assert1 == 0 && read_acc[2] > thresh1 && assertFall == 1 && assertRise2 == 0) {
		//assert2++;
		assertFall = 0;
		assertRise2 = 1;
		counter2 = 0;
		printf("rising edge 2 detected\n");
	}			
	
	if(counter2 > 1000 && assert1 == 0 && read_acc[2] < thresh1 && assertFall == 0 && assertRise2 == 1) {
		assertRise2 = 0;
		assertFall = 0;
		counter2 = 0;
		printf("falling edge 2 detected\n");
		assertDoubleTap = 1;
	}
	
	if(assertDoubleTap == 1) printf("Tap detected\n");	
	
	counter2++;
}

