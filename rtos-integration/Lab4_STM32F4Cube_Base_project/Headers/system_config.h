#include "stm32f4xx_hal.h"
#include "supporting_functions.h"

/* Extern declarations */
extern TIM_Base_InitTypeDef TIM_Base_InitStruct;
extern TIM_HandleTypeDef TIM_HandleStruct;

extern ADC_InitTypeDef ADC1_Init;							
extern ADC_ChannelConfTypeDef ADC1_Channel;
extern ADC_HandleTypeDef ADC1_Handle;

extern GPIO_InitTypeDef GPIOA_Init;						
extern GPIO_InitTypeDef GPIOE_Init;						
extern GPIO_InitTypeDef GPIOD_Init;


/* Function prototypes */
void SystemClock_Config(void);
void TIM3_Config(void);
void ADC_Config(void);
void GPIO_Config(void);

