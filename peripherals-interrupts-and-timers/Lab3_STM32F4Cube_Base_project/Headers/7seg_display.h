#include "stm32f4xx_hal.h"

extern volatile int interrupt_2, interrupt_3, interrupt_5;
extern int parsed[];
extern int displaying[];

void Display(int number, int position);
void Parse(int* store, float sample);
void Show(void);
void Show_Negative(void);
void Display_Alarm(void);
void Reset_Alarm(void);
void Move_Up(void);
void Move_Down(void);
