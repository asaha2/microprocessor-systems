/**
  ******************************************************************************
  * File Name          : SPI_Config.c
  * Description        : Initializes SPI configuration 
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */
	
/* Includes */
#include "SPI_Config.h"

/**
	 * @brief Initializes SPI configuration specific to GPIO pins and peripheral instances
	 * @param void
   * @retval void
   */
void SPI_Init1(){

	/* Handle structure declarations */ 
	GPIO_InitTypeDef GPIO_InitStructure_2;

	/* Enable SPIx and GPIOx interface clock */ 
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
		
	/* SPI SCK pin configuration */
  GPIO_InitStructure_2.Pin = NUCLEO_SPI_SCK_PIN;
	GPIO_InitStructure_2.Alternate = NUCLEO_SPI_AF;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(NUCLEO_SPI_GPIO_PORT, &GPIO_InitStructure_2);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure_2.Pin =  NUCLEO_SPI_MOSI_PIN;
	GPIO_InitStructure_2.Alternate = NUCLEO_SPI_AF;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(NUCLEO_SPI_GPIO_PORT, &GPIO_InitStructure_2);

  /* SPI MISO pin configuration */
  GPIO_InitStructure_2.Pin = NUCLEO_SPI_MISO_PIN;
	GPIO_InitStructure_2.Alternate = NUCLEO_SPI_AF;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(NUCLEO_SPI_GPIO_PORT, &GPIO_InitStructure_2);
	
	/* Configure SPI nSS pin as output push-pull */ 
	GPIO_InitStructure_2.Pin = NUCLEO_SPI_CS_PIN;
	GPIO_InitStructure_2.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure_2.Pull = GPIO_PULLUP;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(NUCLEO_SPI_CS_GPIO_PORT, &GPIO_InitStructure_2);
	
	/* Deselect : Chip Select high */
  HAL_GPIO_WritePin(NUCLEO_SPI_CS_GPIO_PORT, NUCLEO_SPI_CS_PIN, GPIO_PIN_SET);
				
	GPIO_InitStructure_2.Pin = GPIO_PIN_1;
	GPIO_InitStructure_2.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(NUCLEO_SPI_CS_GPIO_PORT, &GPIO_InitStructure_2);

	/* Interrupt configuration for pushbutton */
	GPIO_InitStructure_2.Pin = GPIO_PIN_13;
	GPIO_InitStructure_2.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure_2);

	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);	
	
	/*  */ 
	HAL_SPI_DeInit(&SpiHandle_2);
  SpiHandle_2.Instance 							  = SPI2;
  SpiHandle_2.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_128;
  SpiHandle_2.Init.Direction 					= SPI_DIRECTION_2LINES;
  SpiHandle_2.Init.CLKPhase 					= SPI_PHASE_1EDGE;
  SpiHandle_2.Init.CLKPolarity 				= SPI_POLARITY_LOW;
  SpiHandle_2.Init.CRCCalculation			= SPI_CRCCALCULATION_DISABLED;
  SpiHandle_2.Init.CRCPolynomial 			= 7;
  SpiHandle_2.Init.DataSize 					= SPI_DATASIZE_8BIT;
  SpiHandle_2.Init.FirstBit 					= SPI_FIRSTBIT_MSB;
  SpiHandle_2.Init.NSS 								= SPI_NSS_SOFT;
  SpiHandle_2.Init.TIMode 						= SPI_TIMODE_DISABLED;
  SpiHandle_2.Init.Mode 							= SPI_MODE_MASTER;
	if(HAL_SPI_Init(&SpiHandle_2) != HAL_OK) printf ("ERROR: Error in initialising SPI2 \n");
  
	__HAL_SPI_ENABLE(&SpiHandle_2);		
}

/**
	 * @brief Initializes SPI configuration specific to GPIO pins and peripheral instances 
	 * @param void
   * @retval void
	 * @note This function is a redundant implementation and can be disregarded
   */
void SPI_Init2(){

	/* Handle structure declarations */ 
	GPIO_InitTypeDef GPIO_InitStructure_2;

	/* Enable SPIx and GPIOx interface clock */ 
	__HAL_RCC_SPI2_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
		
	/* SPI SCK pin configuration */
  GPIO_InitStructure_2.Pin = GPIO_PIN_3;
	GPIO_InitStructure_2.Alternate = GPIO_AF6_SPI3;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure_2);

  /* SPI  MOSI pin configuration */
  GPIO_InitStructure_2.Pin =  GPIO_PIN_5;
	GPIO_InitStructure_2.Alternate = GPIO_AF6_SPI3;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure_2);

  /* SPI MISO pin configuration */
  GPIO_InitStructure_2.Pin = GPIO_PIN_4;
	GPIO_InitStructure_2.Alternate = GPIO_AF6_SPI3;
	GPIO_InitStructure_2.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure_2.Pull = GPIO_NOPULL;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStructure_2);
	
	/* Configure SPI nSS pin as output push-pull */ 
	GPIO_InitStructure_2.Pin = GPIO_PIN_4;
	GPIO_InitStructure_2.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure_2.Pull = GPIO_PULLUP;
	GPIO_InitStructure_2.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure_2);
	
	/* Deselect : Chip Select high */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
					
	/* SPI handle configuration */ 
	HAL_SPI_DeInit(&SpiHandle_3);
  SpiHandle_2.Instance 							  = SPI3;
  SpiHandle_2.Init.BaudRatePrescaler 	= SPI_BAUDRATEPRESCALER_128;
  SpiHandle_2.Init.Direction 					= SPI_DIRECTION_2LINES;
  SpiHandle_2.Init.CLKPhase 					= SPI_PHASE_1EDGE;
  SpiHandle_2.Init.CLKPolarity 				= SPI_POLARITY_LOW;
  SpiHandle_2.Init.CRCCalculation			= SPI_CRCCALCULATION_DISABLED;
  SpiHandle_2.Init.CRCPolynomial 			= 7;
  SpiHandle_2.Init.DataSize 					= SPI_DATASIZE_8BIT;
  SpiHandle_2.Init.FirstBit 					= SPI_FIRSTBIT_MSB;
  SpiHandle_2.Init.NSS 								= SPI_NSS_SOFT;
  SpiHandle_2.Init.TIMode 						= SPI_TIMODE_DISABLED;
  SpiHandle_2.Init.Mode 							= SPI_MODE_MASTER;
	if(HAL_SPI_Init(&SpiHandle_3) != HAL_OK) printf ("ERROR: Error in initialising SPI2 \n");
  
	__HAL_SPI_ENABLE(&SpiHandle_3);		
}

/**
  * @brief  Writes one byte to via SPI
  * @param  byte: the single byte of data to be written
	* @retval static: any data received on the SPI bus
  */
static uint8_t SPI_SendByte(uint8_t byte){
	__IO uint32_t  LIS3DSHTimeout = 10000;
	while (__HAL_SPI_GET_FLAG(&SpiHandle_2, SPI_FLAG_TXE) == RESET){
    if((LIS3DSHTimeout--) == 0) return 0;
  }
  SPI_SendData(&SpiHandle_2, byte);
	
	LIS3DSHTimeout = 10000;
	while (__HAL_SPI_GET_FLAG(&SpiHandle_2, SPI_FLAG_RXNE) == RESET){
    if((LIS3DSHTimeout--) == 0){
			return 0;
		}
  }
	return SPI_ReceiveData(&SpiHandle_2);
}

/**
  * @brief  Reads a block of data via SPI
  * @param  pBuffer : pointer to the buffer that receives the data
  * @param  NumByteToRead : number of bytes to read
  * @retval None
  */
void SPI_Read(uint8_t* pBuffer, uint16_t NumByteToRead){
	while(NumByteToRead > 0x00){
			*pBuffer = SPI_SendByte(DUMMY_BYTE);
			NumByteToRead--;
			pBuffer++;
	}
}

/**
  * @brief  Writes a block of data via SPI
  * @param  pBuffer : pointer to the buffer that contains the data
  * @param  NumByteToRead : number of bytes to write
  * @retval None
  */
void SPI_Write(uint8_t* Buffer, uint16_t NumByteToWrite){
	while(NumByteToWrite >= 0x01){
		SPI_SendByte(*Buffer);
		NumByteToWrite--;
		Buffer++;
	}
}
	



