
typedef struct kalman_struct{
	float q; 		// process noise covariance
	float r; 		// measurement noise covariance
	float x; 		// estimated value
	float p; 		// estimation error covariance
	float k; 		// adaptive kalman filter gain
}kalman_state;

void Reset(kalman_state* kinit);
int Kalmanfilter_C(float InputArray, float* OutputArray, kalman_state* kstate);
