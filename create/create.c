// Created on Thu June 11 2015

// External
#include "./generic.h"
#include "./create_drive.h"
#include "./routines.h"

// States
#define s_TEST -1
#define s_START 0
#define s_MOVETOMESA 1
#define s_SWEEPBOTGUY 2
#define s_PUTCUBESINCALDERA 3
#define s_MOVEUNDERMESA 4
#define s_GRABCUBES 5
#define s_PUTCUBESINCALDERA_2 6
	
#define s_END 1337

// Menu
#include "./menu.h"
#define MENU_SIZE 8
struct menuitem menu[] = {
	{s_TEST, "test"},
	{s_START,"seeding"},
	{s_MOVETOMESA,"move to mesa"},
	{s_SWEEPBOTGUY,"sweep botguy"},
	{s_PUTCUBESINCALDERA,"score first pair"},
	{s_MOVEUNDERMESA,"move under mesa"},
	{s_GRABCUBES,"grab other pair"},
	{s_PUTCUBESINCALDERA_2, "sweep and score second pair"}
};

int main()
{
	printf("Establishing connection...\n");

	create_connect();
	enable_servos();

	printf("Connection successful! v. 1.0.7\n");
	
	init();
	Get_Mode(MENU_SIZE);
	
	if (currstate == s_PUTCUBESINCALDERA_2) {
		raise_arm_full();
		closeClaw();
	}
	start(); // Time

	while (currstate != s_END) {

		state (s_TEST) {
			
			raise_arm(2000);
			create_forward(mm(15), 220);
			create_block();
			msleep(1000);
			create_backward(mm(15), 200);
			create_block();
			
			next(s_END);
			
		}
		
		state (s_START) {

			create_left(30, 0, 90);
			create_block();
			//closeClaw();
			servo_set(CUBE_SERVO, CUBE_CLOSED, 1);
			raise_arm_full();
			//create_square();
			create_backward(mm(3), 100);	// "Square"
			now();
			next(s_MOVETOMESA);
		}

		state (s_MOVETOMESA) {

			create_left(85, 0, 200);
			create_forward(mm(25), 200);
			create_block();

			msleep(1000); // Wait for the create to "calm down"

			//lower_arm(200);
			now();
			next(s_SWEEPBOTGUY);

		}

		state (s_SWEEPBOTGUY) {

			create_right(160, 0, 380);
			lower_arm(200);
			create_block();
			raise_arm_full();
			msleep(1000);

			create_left(77, 0, 200); // readjust
			//create_backward(mm(4), 200);
			create_block();
			now();
			next(s_PUTCUBESINCALDERA);
		}

		state (s_PUTCUBESINCALDERA) {

			create_forward_until_touch(200, 180);
			create_block();
			// create_right(3, 0, 200);
			// create_right(8, 0, 200);
			create_forward(mm(5), 300);
			create_block();
			msleep(1000);
			openClaw();
			create_right(90, 0, 150);
			create_forward(mm(6), 150);
			create_block();

			now();
			next(s_MOVEUNDERMESA);

		}

		state (s_MOVEUNDERMESA) {

			// create_drive_direct_dist(150, 250, mm(26.5));
			
			msleep(1000);
			create_left(90, 0, 150);
			
			//create_square();
			create_backward(mm(28), 150);
			create_block();

			create_forward(mm(12), 150);
			create_block();
			create_left(90, 0, 200);
			create_block();

			msleep(1000);
			create_backward(mm(15), 200);
			create_block();

			lower_arm(2700);
			create_forward(mm(56), 200);
			create_block();

			// create_right(90, mm(20), 250);
			// create_block();
			// lower_arm(2700);
			// create_forward_until_touch(200, 200);
			// create_backward(mm(13), 200);
			// create_right(86, 0, 200);
			// create_backward(mm(20), 150);
			// create_forward(mm(64), 200);
			// create_block();
			now();
			next(s_GRABCUBES);

		}

		state (s_GRABCUBES) {

			openClawPartial(CUBE_OPEN + 100);
			lower_arm(2500);
			// create_backward_until_confirm();
			create_backward(mm(5), 90);
			create_block();
			closeClaw();
			raise_arm(2500);

			create_backward(mm(50), 200);
			create_block();
			raise_arm_full();

			next(s_PUTCUBESINCALDERA_2);

		}

		state (s_PUTCUBESINCALDERA_2) {

			create_right(91, 0, 150);
			create_backward(mm(17), 150);
			create_left(89, 0, 150);
			create_forward(mm(10), 100);
			create_block();

			msleep(500);
			create_right(38, mm(10), 150);
			create_block();
			msleep(500);
			create_backward(mm(2), 100);
			create_block();

			lower_arm(660);
			create_forward(mm(2), 100);
			create_block();

			msleep(1000);
			create_right(20, mm(5), 150);
			create_block();
			msleep(1000);
			create_right(25, mm(5), 150);
			create_block();
			create_drive_direct_dist(180, 205, mm(25));
			create_block();

			openClaw();
			raise_arm_full();
			create_right(90, 0, 200);

			now();
			next(s_END);

		}

	}

	ao();
	create_disconnect();
}
