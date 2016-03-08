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
// #define ARM_MATH_CM4
// #include "arm_math.h"
#include "math.h"


/* Private variables ---------------------------------------------------------*/


typedef struct kalman_struct{
	double q; 		// process noise covariance
	double r; 		// measurement noise covariance
	double x; 		// estimated value
	double p; 		// estimation error covariance
	double k; 		// adaptive kalman filter gain
}kalman_state;

LIS3DSH_InitTypeDef LIS3DSH_InitStruct;
LIS3DSH_DRYInterruptConfigTypeDef LIS3DSH_InterruptConfigStruct;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config	(void);
void Reset(kalman_state* kinit);
int Kalmanfilter_C(int InputArray, int* OutputArray, kalman_state* kstate);

int main(void){	
		
	uint8_t out_x_l, out_x_h;
	uint8_t out_y_l, out_y_h; 
	uint8_t out_z_l, out_z_h;
	
	int out_x, out_y, out_z;
	int output_x[1] = {0};
	int output_y[1] = {0};
	int output_z[1] = {0};
	
	kalman_state kstate_x;
	kalman_state kstate_y;
	kalman_state kstate_z;
	
	float den_pitch, den_roll;
	float pitch, roll;
	
	/* MCU Configuration----------------------------------------------------------*/
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
	
  /* Initialize all configured peripherals */
	LIS3DSH_InitStruct.AA_Filter_BW = LIS3DSH_AA_BW_50;
	LIS3DSH_InitStruct.Axes_Enable = LIS3DSH_XYZ_ENABLE;
	LIS3DSH_InitStruct.Continous_Update = LIS3DSH_ContinousUpdate_Disabled;
	LIS3DSH_InitStruct.Full_Scale = LIS3DSH_FULLSCALE_2;
	LIS3DSH_InitStruct.Power_Mode_Output_DataRate = LIS3DSH_DATARATE_100;
	LIS3DSH_InitStruct.Self_Test = LIS3DSH_SELFTEST_NORMAL;
	
	LIS3DSH_InterruptConfigStruct.Dataready_Interrupt = LIS3DSH_DATA_READY_INTERRUPT_ENABLED;
	LIS3DSH_InterruptConfigStruct.Interrupt_signal = LIS3DSH_ACTIVE_HIGH_INTERRUPT_SIGNAL;
	LIS3DSH_InterruptConfigStruct.Interrupt_type = LIS3DSH_INTERRUPT_REQUEST_PULSED;
	
	LIS3DSH_Init(&LIS3DSH_InitStruct);
	LIS3DSH_DataReadyInterruptConfig(&LIS3DSH_InterruptConfigStruct);
	
	Reset(&kstate_x);	
	Reset(&kstate_y);
	Reset(&kstate_z);

	while (1){
		
		LIS3DSH_Read(&out_x_l, LIS3DSH_OUT_X_L, 1);
		LIS3DSH_Read(&out_x_h, LIS3DSH_OUT_X_H, 1);
		LIS3DSH_Read(&out_y_l, LIS3DSH_OUT_Y_L, 1);
		LIS3DSH_Read(&out_y_h, LIS3DSH_OUT_Y_H, 1);
		LIS3DSH_Read(&out_z_l, LIS3DSH_OUT_Z_L, 1);
		LIS3DSH_Read(&out_z_h, LIS3DSH_OUT_Z_H, 1);
		
		out_x = (out_x_h & out_x_l);
		out_y = (out_y_h & out_y_l);
		out_z = (out_z_h & out_z_l);
		
		if(!Kalmanfilter_C(out_x, output_x, &kstate_x) && !Kalmanfilter_C(out_y, output_y, &kstate_y) 
			&& !Kalmanfilter_C(out_z, output_z, &kstate_z)){				
				// printf("%u | %u | %u\n", output_x[0], output_y[0], output_z[0]);
				den_pitch = sqrt(pow(output_y[0], 2) + pow(output_z[0], 2));
				den_roll 	= sqrt(pow(output_x[0], 2) + pow(output_z[0], 2));
				pitch = atan(output_x[0] / den_pitch) * (180 / 3.1416);
				roll = atan(output_y[0] / den_roll) * (180 / 3.1416);
				printf("%f | %f\n", pitch, roll);
		}
	}
}

int Kalmanfilter_C(int InputArray, int* OutputArray, kalman_state* kstate){

	/* Update the Kalman state parameters */
	kstate->p = kstate->p + kstate->q;
	kstate->k = kstate->p / (kstate->p + kstate->r);
	kstate->x = kstate->x + kstate->k * (InputArray - kstate->x);
	kstate->p = (1 - kstate->k) * kstate->p;

	OutputArray[0] = kstate->x;

	/* Check for NaN */
	if(kstate->x != kstate->x){
		return 1;
	}
	return 0;
}

/**
	 * @brief This function initializes the Kalman filter struct parameters. The initial values are
	 * decided following rigorous experiments that give the best result for our pertinent sensor
	 * @param kinit*: Pointer to a kalman_state structure
   * @retval void
   */
void Reset(kalman_state* kinit){

	kinit->q = 0.1;
	kinit->r = 0.1;
	kinit->x = 0;
	kinit->p = 0.1;
	kinit->k = 0;
}

/** System Clock Configuration*/
void SystemClock_Config(void){

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType 	= RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState 			 	= RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState 		= RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource 	= RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM 				= 8;
  RCC_OscInitStruct.PLL.PLLN 				= 336;
  RCC_OscInitStruct.PLL.PLLP 				= RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ 				= 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){Error_Handler(RCC_CONFIG_FAIL);};

  RCC_ClkInitStruct.ClockType 			= RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource 		= RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider 	= RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider 	= RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider 	= RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5)!= HAL_OK){Error_Handler(RCC_CONFIG_FAIL);};
	
	/*Configures SysTick to provide 1ms interval interrupts. SysTick is already 
	  configured inside HAL_Init, I don't kow why the CubeMX generates this call again*/
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	/* This function sets the source clock for the internal SysTick Timer to be the maximum,
	   in our case, HCLK is now 168MHz*/
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
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

