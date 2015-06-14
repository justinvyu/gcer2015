// Created on Thu June 11 2015

#include "generic.h"
#include "routines.h"
#include "create_drive.h"

#define mm(inch) inch * 25.4

int main()
{
	create_connect();
	enable_servos();
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);
	
	create_left(30, 0, 200);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_CLOSED);
	msleep(300);
	
	raise_arm();

	create_drive_direct_dist(200, 100, mm(20));
	create_block();
	create_drive_direct_dist(150, 150, mm(6));
	create_block();
	create_drive_direct_dist(100, 250, mm(17));
	create_block();
	create_drive_direct_dist(100, 250, mm(5));
	create_block();
	
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);

	create_disconnect();
}
