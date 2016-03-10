#include "stm32f4xx_hal.h"

extern volatile int interrupt_2, interrupt_3;
extern int parsed[];
extern int displaying[];

void Display(int number, int position);
void Parse(int* store, float sample);
void Show(void);
