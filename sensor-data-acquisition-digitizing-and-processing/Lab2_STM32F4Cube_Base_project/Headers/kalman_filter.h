#include "stdint.h"
#include <stdio.h>

typedef struct kalman_struct{
	double q; 		// process noise covariance
	double r; 		// measurement noise covariance
	double x; 		// estimated value
	double p; 		// estimation error covariance
	double k; 		// adaptive kalman filter gain
}kalman_state;

void Reset(kalman_state* kinit);
int Kalmanfilter_C(double InputArray, double* OutputArray, kalman_state* kstate);
