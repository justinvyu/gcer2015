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
#define BLACK_SEN_THRESH 750 // replace with calibration
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
	for(i=0; i<20; i++){
		ssp(0,1333);
		msleep(170);
		ssp(0,1260);
		msleep(170);
	}
	disable_servos();
	motor(REVOLVE_MOTOR, 100);

}
	
void Abyssal_Voyage() {
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 100); 
	motor(MOT_RIGHT, 100);//jump
	msleep(1500);
	drive_off();
	motor(MOT_LEFT, 50);
	motor(MOT_RIGHT, 30);//front square up
	msleep(3000);
	drive_off();
	motor(MOT_LEFT, -100);
	msleep(400);
	motor(MOT_RIGHT, 100);//rotate
	msleep(600);
	drive_off();
	motor(MOT_RIGHT, -100);
	motor(MOT_LEFT, -100);//back square up
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

void Chomp() {//first section
	cmpc(MOT_LEFT);
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 1);
	while(1){
		if(gmpc(MOT_LEFT) > 6800){
			motor_off();
			msleep(500);
			break;
		}else if(gmpc(MOT_LEFT) > 4500 && gmpc(MOT_LEFT) < 5200){
			motor(MOT_RIGHT,90);
		}else{
			int val = analog10(lightR);
			if(val > BLACK_SEN_THRESH ){//on black
				motor(MOT_RIGHT, 1);
			}else{
				motor(MOT_RIGHT, 100);
			}
			msleep(100);
			printf("%d,%d\n",gmpc(MOT_LEFT),val);
		}
	}
}//7295

void Devour(){//second section
	cmpc(MOT_LEFT);
	motor(REVOLVE_MOTOR, 100);
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 1);
	while(1){
		int val = analog10(lightR);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, 1);
		}else{
			motor(MOT_RIGHT, 100);
		}
		msleep(100);
		if(gmpc(MOT_LEFT) > 4050){
			break;
		}
	}
	motor_off();
	motor(MOT_LEFT, 70);
	motor(MOT_RIGHT, 70);
	msleep(5000);//sauare up
}

void Acquired_Taste(){//dump
	motor_off();
	shake();
	ao();
	enable_servos();
	servo_set(0, 450,4);//half way up
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -30);//back up
	msleep(2000); 
	servo_set (0, 20, 2);//full up
	ao();
	motor(MOT_LEFT, 40);
	motor(MOT_RIGHT, 30);//unjam if jammed
	msleep(1000);
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -30);//redump
	msleep(1000);
	ao();
	disable_servos();
	msleep(2000);
	enable_servos();
	motor(MOT_LEFT, 60);
	motor(MOT_RIGHT, 30);
	servo_set (0, 700, 2);//forward and drop
	motor(MOT_LEFT, -40);
	motor(MOT_RIGHT, -30);
	servo_set (0, 800, 2);
	disable_servos();	
}

void startingT() {
	//calibrate();
	
	motor(MOT_LEFT, 80);
	motor(MOT_RIGHT, 90);
	msleep(3000);
}

void Tougue_Lash(){
	cmpc(MOT_LEFT);
	motor(MOT_LEFT, -50);
	motor(MOT_RIGHT, -100);
	while(1){
		int val = analog10(lightB);
		if(val > BLACK_SEN_THRESH ){//on black
			motor(MOT_RIGHT, -1);
		}else{
			motor(MOT_RIGHT, -100);
		}
		msleep(100);
		if(gmpc(MOT_LEFT) < -3500){
			break;
		}
	}
	motor_off();// extra bit
	//msleep(5000);
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

void dance(){
	int i=0;
	enable_servos();
	while(1){
		if(i%6<3){
			motor(MOT_LEFT, 40);
			motor(MOT_RIGHT, 30);
		}else{
			motor(MOT_LEFT, -40);
			motor(MOT_RIGHT, -30);
		}
		ssp(0,1133);
		msleep(200);
		ssp(0,1060);
		msleep(200);
		now();
		i++;
	}
	disable_servos();
}

int main() {	
	wait_for_light(LIGHT_SENS);
	//shake();
	//startingT();
	start();
	shut_down_in(119);
	Abyssal_Voyage();
	Chomp();
	now();
	Acquired_Taste();
	Devour();
	Tougue_Lash();
	Acquired_Taste();
	//dance();
	now();
}
