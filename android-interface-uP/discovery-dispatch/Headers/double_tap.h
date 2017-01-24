/**
  ******************************************************************************
  * File Name          : double_tap.h
  * Description        : Associated header file for 'double_tap.c'
	* Author						 : Aditya Saha, Habib Ahmed, Taha Saifuddin, Richard Cheung
	* Version            : 1.0.0
	* Date							 : April 17th, 2016
  ******************************************************************************
  */
	
/* Extern declarations */
extern float read_acc[3];
extern float thresh1;
extern int assert1, assert2, assertFall, assertRise2, assertDoubleTap, counter2;

/* Function prototypes */
void double_tap(void);

