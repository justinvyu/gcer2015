// Created on Wed June 17 2015

// External
#include "./drive.h"
#include "./generic.h"
#include "./routines.h"


// State
#define s_START 0
#define s_GETFIRSTHALFTRIBBLES 1
#define s_SCOREFIRSTHALF 2
#define s_MOVEUNDERMIDDLE 3
#define s_GETSECONDHALFTRIBBLES 4
#define s_SCORESECONDHALF 5

// Tophat things
#define lightR 1
#define lightB 2
#define BLACK_SEN_THRESH 700 // replace with calibration
int black_sen_thresh;

#define s_END 1337

#define LIGHT_SENS 3

// Menu
#define MENUSIZE 6
#include "./menu.h"
struct menuitem menu[] = {
	{s_START,"seeding"},
	{s_GETFIRSTHALFTRIBBLES,"get first half"},
	{s_SCOREFIRSTHALF,"score first half"},
	{s_MOVEUNDERMIDDLE,"move under caldera"},
	{s_GETSECONDHALFTRIBBLES,"get second half"},
	{s_SCORESECONDHALF,"score second half"}
};

void motor_off() {
	off(MOT_LEFT);
	off(MOT_RIGHT);
 }

void shake() {
	off(REVOLVE_MOTOR);
	ao();
	enable_servos();
	int i;
	for(i=0; i<10; i++){
		ssp(0,1333);
		msleep(150);
		ssp(0,1230);
		msleep(150);
	}
	disable_servos();
	motor(REVOLVE_MOTOR, 100);

}
	
void Abyssal_Voyage() {
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 100); 
	motor(MOT_RIGHT, 100);
	msleep(1500);
	motor(MOT_LEFT, 30);
	motor(MOT_RIGHT, 30);
	msleep(3000);
	ao();
	motor(MOT_LEFT, -100);
	msleep(600);
	ao();
	motor(MOT_RIGHT, 100);
	msleep(400);
	ao();
	motor(MOT_RIGHT, -1);
	motor(MOT_LEFT, -60);
	msleep(2500);
	motor(MOT_LEFT, 60);
	msleep(500);
	ao();
	motor(MOT_RIGHT, 60);
	msleep(500);
	ao();
	motor(MOT_RIGHT, -1);
	motor(MOT_LEFT, -60);
	msleep(2500);
}


void Cali () {
	// change black_sen_thresh
	printf("Light values: (off tape)\n");
	printf("Press any button to start collecting light data...\n");
	while(a_button() == 0 || b_button() == 0 || c_button() == 0) {
		msleep(100);
	}
	printf("Collecting light data..........\n");
	int num = 10;
	int i, light_sum = 0;
	for(i = 0; i < num; i++) {
		light_sum += analog10(lightR);
		msleep(100);
	}
	int light_avg = light_sum / num;
	printf("Light avg : %d\n", light_avg);

	printf("\nDark values: (on tape)\n");
	printf("Press any button to start collecting dark data...\n");
	while(a_button() == 0 || b_button() == 0 || c_button() == 0) {
		msleep(100);
	}
	int dark_sum = 0;
	for(i = 0; i < num; i++) {
		dark_sum += analog10(lightR);
		msleep(100);
	}
	int dark_avg = dark_sum / num;
	printf("Dark avg : %d\n", dark_avg);
	
	printf("Calculating sensor threshold");
	msleep(1000);
	
	int sen_thresh = (light_avg + dark_avg) / 2;
	printf("Your sensor threshold is %d", sen_thresh);
	
	black_sen_thresh = sen_thresh;
}

void Chomp() {
	cmpc(MOT_LEFT);
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 70);
	motor(MOT_RIGHT, 1);
	while(1){
		int val = analog10(lightR);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, 1);
		}else{
			motor(MOT_RIGHT, 100);
		}
		msleep(100);
		printf("%d,%d\n",gmpc(MOT_LEFT),val);
		if(gmpc(MOT_LEFT) > 7000){
			motor_off();
			break;
		}
	}
}//7295

void Devour(){
	cmpc(MOT_LEFT);
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 70);
	motor(MOT_RIGHT, 1);
	while(1){
		int val = analog10(lightR);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, 1);
		}else{
			motor(MOT_RIGHT, 100);
		}
		msleep(100);
		if(gmpc(MOT_LEFT) > 3850){
			break;
		}
	}
	motor_off();
	motor(MOT_LEFT, 70);
	motor(MOT_RIGHT, 70);
	msleep(5000);
}

void Acquired_Taste(){
	motor_off();
	shake();
	ao();
	enable_servos();
	servo_set(0, 450,4);
	motor(MOT_LEFT, -15);
	motor(MOT_RIGHT, -1);
	msleep(5000); 
	servo_set (0, 20, 2);
	ao();
	motor(MOT_LEFT, 15);
	motor(MOT_RIGHT, 1);
	msleep(1000);
	motor(MOT_LEFT, -15);
	motor(MOT_RIGHT, -1);
	msleep(1000);
	disable_servos();
	msleep(4000);
	enable_servos();
	motor(MOT_LEFT, 15);
	motor(MOT_RIGHT, 1);
	servo_set (0, 600, 4);
	motor(MOT_LEFT, -15);
	motor(MOT_RIGHT, -1);
	servo_set (0, 800, 2);
	disable_servos();
	msleep(300);
	enable_servos();
	ssp(0,950);
	msleep(700);
	disable_servos();
}

void startingT() {
	//calibrate();
	motor(MOT_LEFT, -100);
	msleep(600);
	ao();
	motor(MOT_RIGHT, 100);
	msleep(400);
	ao();
	motor(MOT_RIGHT, -1);
	motor(MOT_LEFT, -60);
	msleep(2500);
	
}

void Tougue_Lash(){
	cmpc(MOT_LEFT);
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, -100);
	while(1){
		int val = analog10(lightB);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, -1);
		}else{
			motor(MOT_RIGHT, -100);
		}
		msleep(100);
		if(gmpc(MOT_LEFT) < -3300){
			break;
		}
	}
	motor_off();
	msleep(5000);
}

void backToMe() {
	ao();
	msleep(5000);
	cmpc(MOT_LEFT);
	motor(MOT_LEFT, -60);
	motor(MOT_RIGHT, -100);
	while(1){
		int val = analog10(lightB);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, -1);
		}else{
			motor(MOT_RIGHT, -100);
		}
		msleep(100);
	}
	motor_off();
	msleep(5000);
}

int main() {	
	
	//wait_for_light(LIGHT_SENS);
	//shut_down_in(119);
	start();
	Abyssal_Voyage();
	Chomp();
	now();
	Acquired_Taste();
	Devour();
	Tougue_Lash();
	Acquired_Taste();
	now();
}
