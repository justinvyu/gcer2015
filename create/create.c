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
#define s_MOVEUNDERMESA 4
#define s_GRABCUBES 5
#define s_PUTCUBESINCALDERA_2 6

#define s_END 1337

// Menu
#define MENUSIZE 7
#include "./menu.h"
struct menuitem menu[] = {
	{s_START,"seeding"},
	{s_MOVETOMESA,"move to mesa"},
	{s_SWEEPBOTGUY,"sweep botguy"},
	{s_PUTCUBESINCALDERA,"score first pair"},
	{s_MOVEUNDERMESA,"move under mesa"},
	{s_GRABCUBES,"grab other pair"},
	{s_PUTCUBESINCALDERA_2, "sweep and score second pair"}};

int main()
{
	printf("Establishing connection...\n");

	create_connect();
	enable_servos();

	printf("Connection successful! v. 1.0.6\n");
	
	init();

	Get_Mode();
	start(); // Time

	while (currstate != s_END) {

		state (s_START) {

			create_left(30, 0, 100);
			create_block();
			closeClaw();
			raise_arm_full();
			create_backward(mm(3), 100);	// "Square"
			now();
			next(s_MOVETOMESA);
		}

		state (s_MOVETOMESA) {

			create_left(87, 0, 200);
			create_forward(mm(25), 200);
			create_block();
			msleep(1000); // Wait for the create to "calm down"
			now();
			next(s_SWEEPBOTGUY);

		}

		state (s_SWEEPBOTGUY) {

			create_right(130, 0, 330);
			create_block();
			msleep(1000);
			create_left(45, 0, 200); // readjust
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
			openClaw();
			create_right(90, 0, 150);
			create_block();

			now();
			next(s_MOVEUNDERMESA);

		}

		state (s_MOVEUNDERMESA) {

			// create_drive_direct_dist(150, 250, mm(26.5));
			
			msleep(1000);
			create_left(88, 0, 150);
			create_backward(mm(30), 150);
			create_forward(mm(12), 150);
			create_left(90, 0, 200);
			create_block();
			msleep(1000);
			create_backward(mm(15), 200);
			create_block();

			lower_arm(2700);
			create_forward(mm(48), 200);
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
			lower_arm(3000);
			// create_backward_until_confirm();
			create_backward(mm(5), 90);
			create_block();
			closeClaw();
			raise_arm(2500);
			next(s_PUTCUBESINCALDERA_2);

		}

		state (s_PUTCUBESINCALDERA_2) {

			// create_backward(mm(45), 200);
			// create_block();
			// raise_arm_full();
			
			// create_right(87, mm(2), 200);
			// create_backward(mm(25), 150);
			// create_forward(mm(2), 200);
			// create_left(88, 0, 200);
			// create_backward(mm(30), 150);
			// create_forward(mm(23), 150);
			// create_backward(mm(3), 150);
			// //create_left(90, 0, 200);
			
			// //create_forward(mm(5), 200);
			// create_right(20, mm(7), 100);
			// create_block();

			// lower_arm(900);
			
			// create_right(48, mm(5), 200);
			// create_drive_direct_dist(185, 220, mm(20));
			// create_drive_direct_dist(200, 185, mm(10));
			// //create_drive_direct_dist(180, 205, mm(28));
			// //create_forward_until_touch(180, 200);
			// create_block();

			// raise_arm_full();
			// create_forward(mm(5), 300);
			// create_block();
			// openClaw();

			now();
			next(s_END);

		}

	}

	ao();
	create_disconnect();
}
