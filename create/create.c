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
	{s_PUTCUBESINCALDERA_2, "sweep and score second pair"}
};

int main()
{
	printf("Establishing connection...\n");

	create_connect();
	enable_servos();

	printf("Connection successful! v. 1.0.4\n");
	
	init();

	Get_Mode();
	start(); // Time

	while (currstate != s_END) {

		state (s_START) {

			create_left(30, 0, 100);
			create_block();
			closeClaw();
			raise_arm();
			create_backward(mm(3), 100);	// "Square"
			now();
			next(s_MOVETOMESA);
		}

		state (s_MOVETOMESA) {

			create_left(87, 0, 200);
			create_forward(mm(26), 200);
			create_block();
			msleep(1000); // Wait for the create to "calm down"
			now();
			next(s_SWEEPBOTGUY);
		}

		state (s_SWEEPBOTGUY) {

			create_right(130, 0, 320);
			create_block();
			msleep(1000);
			create_left(30, 0, 300); // readjust
			//create_backward(mm(4), 200);
			create_block();
			now();
			next(s_PUTCUBESINCALDERA);
		}

		state (s_PUTCUBESINCALDERA) {

			create_left(7, 0, 200);
			create_forward_until_touch(205, 180);
			create_block();
			// create_right(3, 0, 200);
			// create_right(8, 0, 200);
			create_forward(mm(5), 300);
			openClaw();
			create_right(90, 0, 200);
			now();
			next(s_MOVEUNDERMESA);
		}

		state (s_MOVEUNDERMESA) {

			// create_drive_direct_dist(150, 250, mm(26.5));
			create_right(90, mm(20), 250);
			create_block();
			lower_arm(2500);
			create_forward_until_touch(200, 200);
			create_backward(mm(16), 200);
			create_right(88, 0, 200);
			create_forward(mm(52), 200);
			create_block();
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
			next(s_PUTCUBESINCALDERA_2);

		}

		state (s_PUTCUBESINCALDERA_2) {

			create_backward(mm(45), 200);
			create_block();
			raise_arm();
			
			create_right(90, mm(2), 200);
			create_backward(mm(20), 150);
			create_left(90, 0, 200);
			
			create_right(30, mm(10), 100);
			create_block();

			lower_arm(900);
			
			create_right(38, mm(5), 100);
			create_right(20, 0, 200);
			create_forward_until_touch(180, 200);

			raise_arm();
			create_forward(mm(5), 300);
			openClaw();

			now();
			next(s_END);

		}

	}

	ao();
	create_disconnect();
}
