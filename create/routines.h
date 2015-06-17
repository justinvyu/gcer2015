// Created on Wed June 10 2015

// Replace FILE with your file's name
#ifndef _ROUTINES_H_
#define _ROUTINES_H_

#define ssp(servo, position) set_servo_position(servo, position)
#define CUBE_SERVO 2
#define CUBE_CLOSED 1915
#define CUBE_OPEN 900

#define ARM_DOWN_POSITION 5050

#define ARM_MOTOR 0

#define TOUCH 11

void create_forward_until_touch(int rspeed, int lspeed) {
	create_drive_direct(rspeed, lspeed);
	while(get_create_lbump() == 0 || get_create_rbump() == 0) {
		msleep(10);
	}
	create_stop();
}

void raise_arm() {
	motor(ARM_MOTOR, -100);
	while(digital(TOUCH) == 0) {
		msleep(10);
	}
	printf("Touched");
	off(ARM_MOTOR);
}

void lower_arm() {
	clear_motor_position_counter(ARM_MOTOR);
	motor(ARM_MOTOR, 100);
	while (get_motor_position_counter(ARM_MOTOR) < ARM_DOWN_POSITION) {
		msleep(10);
	}
	off(ARM_MOTOR);
}

void raise_arm_half() {
	
	clear_motor_position_counter(ARM_MOTOR);
	motor(ARM_MOTOR, -100);
	while (get_motor_position_counter(ARM_MOTOR) > -1800) {
		msleep(10);
	}
	off(ARM_MOTOR);
}

#endif
