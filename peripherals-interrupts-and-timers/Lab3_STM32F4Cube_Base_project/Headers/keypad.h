#include "stm32f4xx_hal.h"

extern GPIO_InitTypeDef GPIOC_Init;
extern GPIO_InitTypeDef GPIOB_Init;
extern volatile int interrupt_4;
extern int sample_col, sample_row;
extern int temp_col, temp_row;

int Get_Row(void);
int Get_Column(void);
void Set_Row(void);
void Set_Column(void);
char Get_Key(void);
