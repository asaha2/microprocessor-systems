#include "keypad.h"

// row = output; column = input
void Get_Column(void){

	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// row bits set as output
	GPIOB_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOB_Init.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIOB_Init.Pull = GPIO_NOPULL;
	GPIOB_Init.Speed = GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(GPIOB, &GPIOB_Init);	
	
	// output row bits set to logic 0
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
	
	//====================//====================//====================//
	
	// column bits set to logic 1 during idle
	GPIOC_Init.Mode = GPIO_MODE_INPUT;
	GPIOC_Init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIOC_Init.Pull = GPIO_PULLUP;
	GPIOC_Init.Speed = GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(GPIOC, &GPIOC_Init);	
	
	//====================//====================//====================//
	
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET)printf("column 4 ");
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == GPIO_PIN_RESET)printf("column 5 ");
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == GPIO_PIN_RESET)printf("column 6 ");
}

// row = input; column = output
void Get_Row(void){
	
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	// column bits set as output
	GPIOC_Init.Mode = GPIO_MODE_OUTPUT_PP;
	GPIOC_Init.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
	GPIOC_Init.Pull = GPIO_NOPULL;
	GPIOC_Init.Speed = GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(GPIOC, &GPIOC_Init);
	
	// output row bits set to logic 0
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	
	//====================//====================//====================//

	// row bits set to logic 1 during idle
	GPIOB_Init.Mode = GPIO_MODE_INPUT;
	GPIOB_Init.Pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
	GPIOB_Init.Pull = GPIO_PULLUP;
	GPIOB_Init.Speed = GPIO_SPEED_FREQ_HIGH;	
	HAL_GPIO_Init(GPIOB, &GPIOB_Init);
	
	//====================//====================//====================//
	
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET)printf("row 11 \n");
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET)printf("row 12 \n");
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET)printf("row 13 \n");
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET)printf("row 14 \n");
}
