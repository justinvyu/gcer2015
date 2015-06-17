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
	
	create_full();
	
	create_left(30, 0, 100);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_CLOSED);
	msleep(300);
	
	raise_arm();
	//raise_arm_half();
	
	create_backward(mm(3), 100);
	create_left(87, 0, 200);
	
	/*
	create_forward(mm(5.5), 100);
	
	create_right(96, mm(13), 200);
	create_backward(mm(11), 200);
	create_block();
	
	
	motor(ARM_MOTOR, 80);
	msleep(400);//msleep(500);
	off(ARM_MOTOR);
	msleep(1000);
	
	create_left(80, mm(5), 200);
	create_block();
	//create_right(90, 0, 200);
	//create_left(90, 0, 300);
	
	msleep(10000);
	create_forward(mm(3), 100);
	create_right(82, 0, 100);
	create_backward(mm(3), 100);
	create_block();	
	*/
	
	//create_forward(mm(12), 200);
	create_forward(mm(25), 200);
	create_block();
	
	msleep(1000);
	
	create_right(120, 0, 300);
	create_block();
	
	create_backward(mm(5), 100);
	create_block();
	
	msleep(100000);
	
	/*
	motor(ARM_MOTOR, 60);
	msleep(800)//msleep(500);
	off(ARM_MOTOR);
	*/

	//create_backward(mm(2), 100);
	/*
	create_right(40, mm(5), 100);
	create_block();
	
	motor(ARM_MOTOR, 80);
	msleep(800);//msleep(200);//msleep(800);
	off(ARM_MOTOR);
	*/
	
	/*
	create_right(90, mm(15), 200);
	
	//create_right(90, 0, 200);
	create_backward(mm(16), 100);
	create_forward(mm(2), 100);
	create_right(40, 0, 100);
	create_block();

	raise_arm();
	motor(ARM_MOTOR, 80);
	msleep(1000);//msleep(500);
	off(ARM_MOTOR);
	
	msleep(1000);
	
	create_left(110, 0, 500);
	*/
	
	/*
	create_right(38, mm(5), 100);
	create_block();
	*/
	
	motor(ARM_MOTOR, 80);
	msleep(2000);//msleep(500);
	off(ARM_MOTOR);
	create_backward(mm(5), 300);
	
	create_forward_until_touch(185, 200);
	create_block();
	
	create_backward(mm(4), 100);
	create_block();
	
	raise_arm();
	
	create_forward(mm(6), 300);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);
	
	create_right(50, mm(3), 100);
	create_block();
	
	create_backward(mm(8), 100);
	create_block();
	
	create_right(30, 0, 20);
	create_block();
	
	//raise_arm();
	
	//create_backward(mm(2), 200);
	//create_right(10, mm(2), 200);
	//create_drive_direct_dist(150, 200, -mm(10));
	//create_block();
	
	//ssp(CUBE_SERVO, CUBE_OPEN);
	//msleep(300);
	
	//create_backward(mm(5), 200);
	//create_right(90, 0, 200);
	//create_black();
	
	//create_right(10, mm(3), 100);
	//create_block();
	
	//create_backward(mm(5), 100);
	//create_right(30, 0, 20);
	//create_backward(mm(5), 100);
	//create_block();
	
	//ssp(CUBE_SERVO, CUBE_CLOSED);
	lower_arm();

	create_disconnect();
}
