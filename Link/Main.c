// Created on Thu June 11 2015
#include "drive.h"
#inlcude "generic.h"
#include "Han_Solo.h"
#define left_motor 0
#define right_motor 3
#define claw_servo 13
void ping_get(){
	motor(left_motor, -40);
	motor(right_motor, -40);
	servo_set(claw_servo, 1200, 1000);
	msleep(1000);
	
	
	
	}
int main()
{
	
	
	printf("Hello, World!\n");
	
	return 0;
}
