// Created on Thu June 18 2015

#include "create_drive.h"
#include "functions.h"

void flip_flipper() {
	/* msleep(800);
	ssp(FLIPPER_PORT, FLIPPER_OUT);
	msleep(200);*/
	
	msleep(700);
	slow_servo(FLIPPER_PORT, FLIPPER_OUT, 0.4);
	
}

void open_flipper() {
	ssp(FLIPPER_PORT, FLIPPER_OPEN);
	msleep(200);
}

int main()
{
	printf("testing 4");

	
	create_connect(); 
	//set_servo_position(1, 2047);

	//wait_for_light(0); // change the port number to match where your robot 
	shut_down_in(119); // shut off the motors and stop the Create after 119 seconds

	enable_servos();
	
	thread tid = thread_create(flip_flipper);
	thread tid2 = thread_create(open_flipper);
	
	create_drive_direct(185, 0); //for some reason, (left, right)
	msleep(150);
	create_block();
	
	thread_start(tid2);
	thread_start(tid);
	create_drive_straight(500);
	slow_servo(ARM_PORT, ARM_UP, 0.1);
	msleep(1400);
	slow_servo(ARM_PORT, ARM_DOWN, 0.1);
	create_block();
	msleep(200);
	
	thread_wait(tid2);
	thread_wait(tid);
	thread_destroy(tid2);
	thread_destroy(tid);
	
	open_flipper();
	
	/*ssp(ARM_PORT, ARM_MID);
	msleep(200);*/
	
	/*create_drive_straight(-500);
	msleep(100);
	create_block();*/
	
	msleep(1000);
	
	create_drive_direct(110, 80);
	msleep(1500);
	create_block();
	
	create_drive_straight(-500);
	msleep(250);
	create_block();
	
	create_drive_straight(400);
	msleep(200);
	create_block();
	
	ssp(ARM_PORT, ARM_MID);
	msleep(90000);
	
	//arm_shake();
	create_disconnect();
	disable_servos();
	return 0;
}

