// Created on Thu June 11 2015

// External

#include "./generic.h"
#include "./create_drive.h"
#include "./routines.h"

// States

#define s_START 0
#define s_MOVETOMESA 1
#define s_SWEEPBOTGUY 2
#define s_PUTCUBESINCALDERA 3

#define s_END 1337

int main()
{
	printf("Establishing connection...\n");

	create_connect();
	enable_servos();

	printf("Connection successful!\n");
	
	init();

	next(s_START);

	while (currstate != s_END) {

		state (s_START) {

			create_left(30, 0, 100);
			create_block();
			closeClaw();
			raise_arm();
			create_backward(mm(3), 100);	// "Square"
			next(s_MOVETOMESA);
		}

		state (s_MOVETOMESA) {

			create_left(87, 0, 200);
			create_forward(mm(25), 200);
			create_block();
			msleep(1000); // Wait for the create to "calm down"
			next(s_SWEEPBOTGUY);
		}

		state (s_SWEEPBOTGUY) {

			create_right(130, 0, 350);
			create_left(32, 0, 200); // readjust
			create_backward(mm(4), 200);
			create_block();
			next(s_PUTCUBESINCALDERA);
		}

		state (s_PUTCUBESINCALDERA) {

			create_forward_until_touch(190, 200);
			create_block();

			create_right(8, 0, 200);
			create_forward(mm(5), 300);
			openClaw();
			create_right(90, 0, 200);

			next(s_END);
		}

	}
	/*
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
	
	ssp(CUBE_SERVO, CUBE_CLOSED);
	lower_arm();
	*/

	create_disconnect();
}
