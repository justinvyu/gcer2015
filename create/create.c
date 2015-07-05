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
	
	//wait_for_light(LIGHT_SENS);
	shut_down_in(119);
	start(); // Time

	while (currstate != s_END) {

		state (s_TEST) {
			
			// raise_arm(2000);
			// create_forward(mm(15), 220);
			// create_block();
			// msleep(1000);
			// create_backward(mm(15), 200);
			// create_block();
			
			int i, total = 5000, interval = 500;
			for(i = 0; i < total / interval; i++) {
				printf("%d\n", analog10(3));
				msleep(interval);
			}
			
			next(s_END);
			
		}
		
		state (s_START) {

			msleep(2000);
			lower_arm(1000);
			
			create_left(30, 0, 90);
			create_block();
			servo_set(CUBE_SERVO, CUBE_CLOSED, 1);
			raise_arm_full();
			create_backward(mm(2), 150);	// "Square"
			now();
			next(s_MOVETOMESA);

		}

		state (s_MOVETOMESA) {

			create_left(84.5, 0, 200);
			create_forward(mm(24.5), 200);
			create_block();

			msleep(800); // Wait for the create to "calm down"
			now();
			next(s_SWEEPBOTGUY);

		}

		state (s_SWEEPBOTGUY) {

			create_right(160, 0, 380);
			lower_arm(145);
			create_block();
			msleep(500);
			
			create_right(20, 0, 200);
			create_block();

			lower_arm_full();

			// Sweep botguy out of the way if he is to the left of the robot
			create_left(112, 0, 280);
			create_block();
			create_forward(mm(6), 280);
			// Sweep botguy out of the way if he is to the right of the robot & avoid charlie's robot
			create_right(120, 0, 280);
			create_block();
			msleep(200);
			// Push tribbles to prevent tripping later on
			create_forward(mm(5), 200);
			create_backward(mm(5), 200);
			create_block();
			
			raise_arm_full();
			//create_left(102.5, 0, 200);
			
			// Readjust
			create_left(110, 0, 200);
	
			create_block();
			lower_arm(200); 
			now();
			next(s_PUTCUBESINCALDERA);
		}

		state (s_PUTCUBESINCALDERA) {

			create_forward_until_touch(200, 166);
			create_block();
			create_forward(mm(3), 300);
			create_left(1, 0, 200);
			create_block();
			msleep(500);
			openClaw();
			//create_left(3, 0, 200);
			raise_arm_full();
			//create_right(92, 0, 200);
			create_right(90, 0, 200);
			create_forward(mm(6), 200);
			create_block();

			now();
			next(s_MOVEUNDERMESA);

		}

		state (s_MOVEUNDERMESA) {
			
			msleep(500);
			create_left(91, 0, 150);
			create_forward_until_touch(200, 200);
			create_block();
			
			//msleep(500);
			//create_square();
			create_backward(mm(26.5), 200);
			create_block();
			msleep(500);

			create_forward(mm(12), 150);
			create_block();
			create_left(88, 0, 200);
			create_block();

			msleep(500);
			create_backward(mm(15), 200);
			create_block();

			lower_arm(1600);
			//create_forward(mm(56), 320);
			create_forward(mm(62), 320);
			create_block();
			msleep(500);

			now();
			next(s_GRABCUBES);

		}

		state (s_GRABCUBES) {
			
			create_backward(mm(5), 200);
			create_block();
			openClawPartial(CUBE_OPEN + 200);
			lower_arm(2400);
			create_backward(mm(4), 90);
			create_block();
			closeClaw();
			raise_arm(2500);

			create_backward(mm(50), 300);
			create_block();
			raise_arm_full();

			next(s_PUTCUBESINCALDERA_2);

		}

		state (s_PUTCUBESINCALDERA_2) {

			create_right(91, 0, 200);
			create_backward(mm(13), 200);
			create_block();
			msleep(1000);
			create_left(89, 0, 200);
			create_forward(mm(11.5), 200);
			create_block();

			msleep(500);
			create_right(38, mm(9), 150);
			create_block();
			//msleep(500);
			create_backward(mm(5), 100);
			create_block();

			//lower_arm(660);
			lower_arm(700);
			create_forward(mm(2), 100);
			create_block();

			//msleep(200);
			create_right(18, mm(5.5), 150);
			create_block();
			//msleep(200);
			//create_right(24, mm(6), 150);
			create_drive_direct(200, 100);
			msleep(600);
			create_block();
			//create_drive_direct_dist(178, 215, mm(25));
			create_drive_direct_dist(174, 215, mm(25));
			raise_arm(300);
			create_block();
			create_left(1, 0, 200);
			create_block();
			
			//raise_arm_full();
			openClaw();
			closeClaw();
			openClaw();
			raise_arm_full();
			
			// 6th Cube
			create_right(5, 0, 200);
			create_backward(mm(2), 200);
			create_left(13, 0, 150);
			create_forward(mm(1), 200);
			
			create_block();
			extendExtension();
			msleep(500);
			lower_arm(700);
			
			//create_backward(mm(2), 200);
			create_block();
			
			msleep(1000);
			retractExtension();

			now();
			next(s_END);

		}

	}

	ao();
	create_disconnect();
}
