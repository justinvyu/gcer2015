// Created on Wed June 10 2015

// Replace FILE with your file's name
#ifndef _ROUTINES_H_
#define _ROUTINES_H_

#define ssp(servo, position) set_servo_position(servo, position)
#define CUBE_SERVO 2
#define CUBE_CLOSED 1915
#define CUBE_OPEN 900

#define ARM_MOTOR 0

#define TOUCH 12

void raise_arm() {
	motor(ARM_MOTOR, 100);
	while(digital(TOUCH) == 0) {
		msleep(10);
	}
}

void lower_arm() {
	motor(ARM_MOTOR, -60);
	msleep(2000);
}

#endif
