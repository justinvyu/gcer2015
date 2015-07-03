// Created on Sun June 14 2015

#include "drive.h"
#include "generic.h"
#include "functions.h"

#define PICK_SERVO 0
#define SORT_SERVO 1
#define RED 400
#define START 880
#define GREEN 1400
#define GREEN_SERVO 2
#define GREEN_START 100
#define GREEN_DUMP 720
#define RED_SERVO 3
#define RED_START 1400
#define RED_DUMP 700
#define ssp set_servo_position

int main()
{	
	camera_open();
	ssp(SORT_SERVO,START);
	ssp(RED_SERVO,RED_START);
	ssp(GREEN_SERVO,GREEN_START);
	
	//wait_for_light(0);
	shut_down_in(119);
	
	enable_servos();
	reset();
	
	msleep(5000);
	
	right(47,0);
	forward(35);
	right(10,0);
	backward(42);
	full_sort();
	right(10,0);
	other_side();
	ssp(GREEN_SERVO,GREEN_DUMP);
	msleep(1000);
	ssp(GREEN_SERVO,GREEN_START);
	msleep(250);
	ao();
	disable_servos();
}
