/* Includes */
#include "stdint.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

/* Function prototypes */
void Display(int number, int position);
void Parse_Temp(double sample, int input[]);
void Blink(void);
