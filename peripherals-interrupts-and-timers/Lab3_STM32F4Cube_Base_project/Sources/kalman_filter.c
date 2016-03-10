#include "kalman_filter.h"

int Kalmanfilter_C(float InputArray, float* OutputArray, kalman_state* kstate){

	/* Update the Kalman state parameters */
	kstate->p = kstate->p + kstate->q;
	kstate->k = kstate->p / (kstate->p + kstate->r);
	kstate->x = kstate->x + kstate->k * (InputArray - kstate->x);
	kstate->p = (1 - kstate->k) * kstate->p;

	OutputArray[0] = kstate->x;

	/* Check for NaN */
	if(kstate->x != kstate->x){
		return 1;
	}
	return 0;
}

/**
	 * @brief This function initializes the Kalman filter struct parameters. The initial values are
	 * decided following rigorous experiments that give the best result for our pertinent sensor
	 * @param kinit*: Pointer to a kalman_state structure
   * @retval void
   */
void Reset(kalman_state* kinit){

	kinit->q = 0.1;
	kinit->r = 0.1;
	kinit->x = 0;
	kinit->p = 0.1;
	kinit->k = 0;
}
