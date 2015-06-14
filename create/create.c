// Created on Thu June 11 2015

#include "generic.h"
#include "routines.h"
#include "create_drive.h"

int main()
{
	enable_servos();
	create_connect();
	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);
	
	create_left(90, 0, 200);
	create_block();
	
	ssp(CUBE_SERVO, CUBE_CLOSED);
	msleep(300);
	
	raise_arm();	
	lower_arm();
	
	create_disconnect();
}
