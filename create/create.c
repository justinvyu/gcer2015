// Created on Thu June 11 2015

#include "generic.h"
#include "routines.h"
#include "create_drive.h"

#define mm(inch) inch * 25.4

int main()
{
	create_connect();
	enable_servos();
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);
	
	create_left(30, 0, 100);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_CLOSED);
	msleep(300);
	
	raise_arm();

	create_backward(mm(3), 100);
	create_block();
	create_left(90, 0, 200);
	create_block();
	create_forward(mm(25), 200);
	create_block();
	
	create_backward(mm(3), 100);
	create_block();

	motor(ARM_MOTOR, 60);
	msleep(500);
	off(ARM_MOTOR);
	
	create_backward(mm(2), 100);
	create_right(78, mm(5), 100);
	create_block();
	
	motor(ARM_MOTOR, 80);
	msleep(700);
	off(ARM_MOTOR);
	
	create_forward_until_touch(100, 80);
	create_block();
	
	create_backward(mm(2), 100);
	create_block();
	create_right(15, mm(3), 100);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);
	
	create_right(30, 0, 20);
	create_block();

	create_disconnect();
}
