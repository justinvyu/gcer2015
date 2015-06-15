// Created on Thu June 11 2015
#include "drive.h"
#inlcude "generic.h"
#include "Han_Solo.h"
#define left_motor 0
#define right_motor 3
#define claw_servo 13
#define half_claw 1200
#define full_claw 2400
	void half() { 

	servo_set(claw_servo, half_claw, 1000);
	
	}
	void full(){
	servo_set(claw_servo, full_claw, 1000);
		
		}

void ping_get(){
	thread half_tid = thread_create(half);
	thread full_tid = thread_create(full);
	motor(left_motor, -40);
	motor(right_motor, -40);
	thread_start(half_tid);
	msleep(1000);
	thread_wait(half_tid);
	thread_destroy(half_tid);
	motor(left_motor, 40);
	motor(right_motor, 40);
	thread_start(full_tid);
	msleep(1000);
	thread_wait(full_tid);
	thread_destroy(full_tid);
	
	
	
	}
int main()
{
	
	
	printf("Hello, World!\n");
	
	return 0;
}
