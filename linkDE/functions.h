// Created on Wed June 17 2015

// Replace FILE with your file's name
#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define PICK_SERVO 0
#define PICK_START 780
#define PICK_UP 0
#define PICK_DOWN 1420
#define PICK_PUSH 2047
#define SORT_SERVO 1
#define RED 200
#define START 880
#define GREEN 1600
#define GREEN_SERVO 2
#define GREEN_START 100
#define GREEN_DUMP 900
#define RED_SERVO 3
#define RED_START 1400
#define RED_DUMP 700
#define ssp set_servo_position

void slow_servo(int port, int end, float time){
	float curr,start = get_servo_position(port);
	float increment = .01;
	float i = ((end - start)/time)*increment;
	curr = start;
	if(start > end){
		while(curr>end){
			set_servo_position(port,curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	else if(start < end){
		while(curr < end){
			set_servo_position(port, curr);
			curr+=i;
			msleep((long)(increment*1000));
		}
	}
	set_servo_position(port, end);
}

void reset(){
	ssp(PICK_SERVO, PICK_START);
	msleep(250);
}

void sort(){
	printf("Starting sorting \n");
	camera_update();
	float start_time = seconds();
	float curr_time = seconds();
	while(curr_time - start_time < 3){
		curr_time = seconds();
		printf("In loop\n");
		camera_update();
		if(get_object_area(0,1) != -1){
			slow_servo(SORT_SERVO,GREEN,0.5);
			printf("GREEN\n");
			msleep(2000);
			slow_servo(SORT_SERVO,START,1);
			break;
		}
		else if(get_object_area(1,1) != -1){
			slow_servo(SORT_SERVO,RED,0.5);
			printf("RED\n");
			msleep(2000);
			slow_servo(SORT_SERVO,START,1);
			break;
		}
		else{
			printf("NO OBJECT\n");
		}
	}
}

void shake(){
	int i = 0;
	while(i < 5){
		forward(1);
		backward(1);
		i++;
	}
}

void full_sort(){
	int i = 0;
	while(i < 6){
		forward(15);
		right(3,0);
		if(i < 4){
			backward(0.75);
		}
		else{
			forward(2);
		}
		msleep(500);
		left(3,0);
		ssp(PICK_SERVO,PICK_DOWN);
		msleep(1000);
		shake();
		msleep(100);                         
		ssp(PICK_SERVO,PICK_UP);
		msleep(250);
		sort();
		right(4,0);
		backward(15);
		i++;
	}
	reset();
}

void other_side(){
	backward(8);
	ssp(RED_SERVO,RED_DUMP);
	msleep(1500);
	ssp(RED_SERVO,RED_START);
	forward(90);
	right(120,0);
	backward(32);
}

#endif
