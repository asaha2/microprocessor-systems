#include <stdio.h>
#include "arm_math.h"

typedef struct kalman_struct{
	float q; // process noise covariance
	float r; // measurement noise covariance
	float x; // estimated value
	float p; // estimation error covariance
	float k; // adaptive kalman filter gain
}kalman_state;

extern void Kalmanfilter_asm(float* output, float* input, int length, kalman_state* kstate);
int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int length);
void reset(kalman_state* kinit);

float mean(float* input, int length2);
float root(float input);
float squarer(float input);
void subtract(float* sub, float* in1, float* in2, int length);
void misc(float* result, float* diff, int length);
float correlation(float* in, float* out, int length);
void convolve(float* Result, float* in1, float* in2, int length);

void arm_sub_f32(float32_t* pSrcA, float32_t* pSrcB, float32_t* pDst, uint32_t blockSize);
void arm_mean_f32(float32_t* pSrc, uint32_t blockSize, float32_t* pResult);
void arm_std_f32(float32_t*	pSrc, uint32_t 	blockSize, float32_t * pResult);	
void arm_correlate_f32(float32_t* pSrcA, uint32_t srcALen, float32_t* pSrcB, uint32_t srcBLen, float32_t*	pDst);
void arm_conv_f32(float32_t* pSrcA, uint32_t srcALen, float32_t* pSrcB, uint32_t srcBLen, float32_t* pDst);

int main(){
	
	const int length = 5;
	float input[length] = {-0.665365, -0.329988, 0.164465, 0.043962, 0.295885};
	
	float output[length];           	// array for storing Kalman processed values
	float temp[length];             	// array for storing subtraction results
	float temp2[length];	
	float miscresult[2] = {0, 0};   	// array for storing mean and std dev results
	float holder[length];           	// array for storing convolution results
	int i, j;
	float corr_temp[1] = {0};

	/*START OF PART II*/
	kalman_state kstate;
	reset(&kstate);
	//Kalmanfilter_C(input, output, &kstate, length);
	Kalmanfilter_asm(output, input, length, &kstate);
	printf("\n");
	/*END OF PART II*/

	/*START OF PART III*/	
	// subtract
	printf("subtraction:\n");
	subtract(temp, input, output, length);
	arm_sub_f32(input, output, temp2, length);
	for(j = 0; j < length; j++){
		printf("My implementation: %f CMSIS: %f\n", temp[j], temp2[j]);
	}

	// misc
	printf("\n");
	//misc(miscresult, temp, length);
	arm_mean_f32(temp, length, &miscresult[0]);
	arm_std_f32(temp, length, &miscresult[1]);
	printf("mean: %f stdev: %f\n", miscresult[0], miscresult[1]);

	// correlation
	//corr_temp[0] = correlation(input, output, length);
	arm_correlate_f32(input, length, output, length, &corr_temp[0]);
	printf("correlation: %f\n", corr_temp[0]);
	

	// convolution
	printf("\n");
	for(i = 0; i < length; i++){
		holder[i] = 0;
	}
	convolve(holder, input, output, length);
	//arm_conv_f32(input, length, output, length, holder);
	for(i = 0; i < length; i++){
		printf("convolution %f \n", holder[i]);
	}
	/*END OF PART III*/

	return 0;
}

void reset(kalman_state* kinit){

	kinit->q = 0.1;
	kinit->r = 0.1;
	kinit->x = 0;
	kinit->p = 0.1;
	kinit->k = 0;
}

int Kalmanfilter_C(float* InputArray, float* OutputArray, kalman_state* kstate, int length){

	int i;
	int int_temp1 = 0;
	for(i = 0; i < length; i++){
		kstate->p = kstate->p + kstate->q;
		kstate->k = kstate->p / (kstate->p + kstate->r);
		kstate->x = kstate->x + kstate->k * (InputArray[i] - kstate->x);
		kstate->p = (1 - kstate->k) * kstate->p;

		OutputArray[i] = kstate->x;
		printf("Measured position: %f Kalman position: %f\n", InputArray[i], kstate->x);

		if(kstate->x != kstate->x){
			int_temp1++;
		}
	}

	if(int_temp1 > 0){
		printf("Error: NaN!\n");
		return 1;
	}
	return 0;
}

float mean(float* input, int length2){
    
	int i;
	float flt_temp1 = 0;
	for(i = 0; i < length2; i++){
		flt_temp1 = flt_temp1 + input[i];
	}
	return (flt_temp1 / length2);
}

float root(float input){
    
	float flt_temp1;
	int int_temp1, int_temp2, i;
	flt_temp1 = 1;
	int_temp1 = 0;
	int_temp2 = 1000;
	for(i = 0; i < int_temp2; i++){
		int_temp1 = flt_temp1;
		flt_temp1 = (flt_temp1 + input / flt_temp1) / 2;
		if(int_temp1 == flt_temp1){
			break;
		}
	}
	return flt_temp1;
}

float squarer(float input){
    
	return input * input;
}

void subtract(float* sub, float* in1, float* in2, int length){
	
	int i;
	for(i = 0; i < length; i++){
		sub[i] = in1[i] - in2[i];
	}
}

void misc(float* result, float* diff, int length){
    
	float flt_temp1 = 0;
	int i;
	result[0] = mean(diff, length);
	for(i = 0; i < length; i++){
		flt_temp1 = flt_temp1 + squarer(diff[i] - result[0]);
	}

	result[1] = root(flt_temp1 / length - 1);
}

float correlation(float* in, float* out, int length){
    
	float mean_in = mean(in, length);
	float mean_out = mean(out, length);

	float flt_temp1 = 0;
	float flt_temp2 = 0;
	float flt_temp3 = 0;
	int i;
	for(i = 0; i < length; i++){
		flt_temp1 = flt_temp1 + ((in[i] - mean_in) * (out[i] - mean_out));
		flt_temp2 = flt_temp2 + squarer(in[i] - mean_in);
		flt_temp3 = flt_temp3 + squarer(out[i] - mean_out);
	}

	return(flt_temp1 / root(flt_temp2 * flt_temp3));
}

void convolve(float* Result, float* in1, float* in2, int length){
	
	int i, j, int_temp1, int_temp2;
		for (i = 0; i < (length + length - 1); i++){
		Result[i] = 0;
		int_temp1 = 0;
		int_temp2 = 0;

		int_temp1 = (i >= length - 1) ? i - (length - 1) : 0;
		int_temp2 = (i < length - 1) ? i : length - 1;

		for (j = int_temp1; j <= int_temp2; j++){
			Result[i] += in1[j] * in2[i - j];
		}
	}
}
