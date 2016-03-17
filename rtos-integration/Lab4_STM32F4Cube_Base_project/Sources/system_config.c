#include "system_config.h"

void SystemClock_Config(void){
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the
     device is clocked below the maximum system frequency (see datasheet). */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

void ADC_Config(void){
	
	ADC_InitTypeDef ADC1_Init;							
	ADC_ChannelConfTypeDef ADC1_Channel;
	
	/* Configure the ADC peripheral clock */
	__HAL_RCC_ADC1_CLK_ENABLE();
	
	/* Initialize ADC handle, init structure and channel configurations (selects channel 16) */
	ADC1_Handle.Instance = ADC1;
	ADC1_Handle.Init = ADC1_Init;
	
	ADC1_Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
	ADC1_Init.Resolution = ADC_RESOLUTION_12B;
	ADC1_Init.ScanConvMode = DISABLE;
	ADC1_Init.ContinuousConvMode = ENABLE;
	ADC1_Init.DiscontinuousConvMode = DISABLE;
	ADC1_Init.NbrOfDiscConversion = 0;
	ADC1_Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	ADC1_Init.ExternalTrigConv = ADC_SOFTWARE_START;
	ADC1_Init.DataAlign = ADC_DATAALIGN_RIGHT;
	ADC1_Init.NbrOfConversion = 1;
	ADC1_Init.DMAContinuousRequests = DISABLE;
	ADC1_Init.EOCSelection = ADC_EOC_SEQ_CONV;
	
	ADC1_Channel.Channel = ADC_CHANNEL_16;
	ADC1_Channel.Rank = 1;
	ADC1_Channel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC1_Channel.Offset = 0;
	
	/* Use of supporting functions to check proper boot-up of peripherals, report on error */
	if(HAL_ADC_Init(&ADC1_Handle) != HAL_OK){
		// printf("ADC initialization failed!\n");
		Error_Handler(ADC_INIT_FAIL);
	}		
	if(HAL_ADC_ConfigChannel(&ADC1_Handle, &ADC1_Channel) != HAL_OK){
		// printf("Channel configuration failed!\n");
		Error_Handler(ADC_CH_CONFIG_FAIL);
	}
}

void GPIO_Config(void){
	
	GPIO_InitTypeDef GPIOA_Init;						
	GPIO_InitTypeDef GPIOE_Init;						
	GPIO_InitTypeDef GPIOD_Init;
	
	/* Configure the GPIO peripheral clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();	
	__HAL_RCC_GPIOD_CLK_ENABLE();
	
	/* Initializes GPIO PORTS(A, E & D) and specifies pin characteristics */
	GPIOA_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOA_Init.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
	GPIOA_Init.Pull = GPIO_NOPULL;
	GPIOA_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;	
	HAL_GPIO_Init(GPIOA, &GPIOA_Init);
	
	GPIOE_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOE_Init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
	GPIOE_Init.Pull = GPIO_NOPULL;
	GPIOE_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;			
	HAL_GPIO_Init(GPIOE, &GPIOE_Init);
	
	GPIOD_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOD_Init.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIOD_Init.Pull = GPIO_NOPULL;
	GPIOD_Init.Speed = GPIO_SPEED_FREQ_VERY_HIGH;	
	HAL_GPIO_Init(GPIOD, &GPIOD_Init);
}	
