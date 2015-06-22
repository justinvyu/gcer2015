// Created on Thu June 11 2015
#include "drive.h"
#include "generic.h"
#include "Han_Solo.h"
#define left_motor 0
#define right_motor 3
#define belt_motor 2
#define claw_servo 13
#define half_claw 1200
#define full_claw 2400
	void belt() { 

	motor(belt_motor, 100);
	}

int main()
{
	thread pom_get = thread_create(belt);
	thread_start(pom_get);
	forward(25);
	thread_start(pom_get);
	forward(25);
	right(180, 1);
	forward(25);
	
	
	return 0;
}
