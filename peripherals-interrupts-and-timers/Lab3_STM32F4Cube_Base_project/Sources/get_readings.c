#include "get_readings.h"

void Get_Sensor_Data(float alarm){
	
	// printf("Gets here!\n");
	
	// printf("main: counter = %d, interrupt = %d\n", counter, interrupt);
	if(interrupt != 0){
		interrupt = 0;
		// printf("main: counter = %d, interrupt = %d\n", counter, interrupt);
		
		LIS3DSH_ReadACC(read_acc);	
		// printf("%f | %f | %f\n", read_acc[0], read_acc[1], read_acc[2]);
		
		if(!Kalmanfilter_C(read_acc[0], output_x, &kstate_x) && !Kalmanfilter_C(read_acc[1], output_y, &kstate_y) 
				&& !Kalmanfilter_C(read_acc[2], output_z, &kstate_z)){				
				
			// printf("%f | %f | %f\n", output_x[0], output_y[0], output_z[0]);
			den_pitch = sqrt(pow(output_y[0], 2) + pow(output_z[0], 2));
			den_roll 	= sqrt(pow(output_x[0], 2) + pow(output_z[0], 2));
			// pitch = atan(output_x[0] / den_pitch) * (180 / 3.1416);
			roll = atan(output_y[0] / den_roll)  * (180 / 3.1416);
			// printf("%f | %f\n", pitch, roll);					
			Parse(parsed, roll);
			printf("%f\n", roll);
			// printf("%d %d %d %d %d\n", parsed[3], parsed[2], parsed[1], parsed[0], parsed[4]);
		}
	}		
	if(parsed[4] < 0 || parsed[3] < 0 || parsed[2] < 0 || parsed[1] < 0 || parsed[0] < 0) Show_Negative();
	else Show();		
	
	diff_in = roll - alarm;
	arm_abs_f32(&diff_in, &diff_out, 1);
	// if(diff_out <= 4)printf("Trigger alarm!\n");
	if(diff_out <= 4)Display_Alarm();
	
	if(roll < alarm)Move_Up();
	else Move_Down();
	// Reset_Alarm();	
}
