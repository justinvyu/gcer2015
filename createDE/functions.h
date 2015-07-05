// Created on Thu June 18 2015

// Replace FILE with your file's name
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define ARM_PORT 1
#define ARM_UP 610
#define ARM_DOWN 0
#define ARM_MID 25

#define FLIPPER_PORT 0
#define FLIPPER_OPEN 1800
#define FLIPPER_OUT 900

#define ssp set_servo_position

void arm_shake(){
	ssp(ARM_PORT, ARM_DOWN);
	msleep(500);
	ssp(ARM_PORT, ARM_MID);
	msleep(500);
	ssp(ARM_PORT, ARM_DOWN);
	msleep(500);
	ssp(ARM_PORT, ARM_MID);
	msleep(500);
	ssp(ARM_PORT, ARM_DOWN);
	msleep(500);
	ssp(ARM_PORT, ARM_MID);
	msleep(500);
}

void slow_servo(int port, int end, float time){
	float curr,start = get_servo_position(port);
	float increment = .01;
	float i = ((end - start)/time)*increment;
	curr = start;
	if(start > end){
		while(curr>end){
			ssp(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if(start < end){
		while(curr < end){
			ssp(port, curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	ssp(port, end);
}

#endif
