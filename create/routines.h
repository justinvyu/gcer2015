// Created on Wed June 10 2015

// Replace FILE with your file's name
#ifndef _ROUTINES_H_
#define _ROUTINES_H_

// Shortcuts
#define ssp(servo, position) set_servo_position(servo, position)
#define mm(inch) inch * 25.4
#define cmpc(port) clear_motor_position_counter(port)
#define lbump() get_create_lbump() == 0
#define rbump() get_create_rbump() == 0

// Servos, Motors
#define ARM_MOTOR 0
#define CUBE_SERVO 2
#define CUBE_CLOSED 1915
#define CUBE_OPEN 900

// Sensors
#define TOUCH 11
#define CONFIRM_LEVER 12

// Misc. Utils
#define ARM_DOWN_POSITION 5050

#pragma mark - Create Routines

void create_forward_until_touch(int rspeed, int lspeed) { // Allows for slight curvature

	create_drive_direct(rspeed, lspeed);
	while(lbump() || rbump()) {
		msleep(10);
	}
	printf("BUMPED\n");
	create_stop();

}

void create_backward_until_confirm() {

	float start = curr_time();
	create_drive_direct(-200, -200);
	while(digital(CONFIRM_LEVER) == 0 || (curr_time() - start) < 3.5) {
		msleep(10);
	}
	create_stop();

}


#pragma mark - Arm Routines

void raise_arm() {

	motor(ARM_MOTOR, -100);		 // Raise
	while(digital(TOUCH) == 0) { // Wait for touch
		msleep(10);
	}
	off(ARM_MOTOR);

}

void lower_arm_full() {

	cmpc(ARM_MOTOR);
	motor(ARM_MOTOR, 100);
	while (gmpc(ARM_MOTOR) < ARM_DOWN_POSITION) { // Relative to the arm at the highest position
		msleep(10);
	}
	off(ARM_MOTOR);

}

void lower_arm(float time) {

	motor(ARM_MOTOR, 100);
	msleep(time);
	off(ARM_MOTOR);

}

void raise_arm_half() {
	
	cmpc(ARM_MOTOR);
	motor(ARM_MOTOR, -100);
	while (gmpc(ARM_MOTOR) > -1800) { // Negative because moving the arm up moves in a negative direction
		msleep(10);
	}
	off(ARM_MOTOR);

}

#pragma mark - Cube Functions (Servo)

void openClaw() {

	ssp(CUBE_SERVO, CUBE_OPEN);
	msleep(300);

}

void openClawPartial(int pos) {

	ssp(CUBE_SERVO, pos);
	msleep(300);

}

void closeClaw() {

	ssp(CUBE_SERVO, CUBE_CLOSED);
	msleep(300);
}

#pragma mark - Utility Functions

//
// Initializes servos & sets up create_full
// 
// @precondition	Servos are enabled, Create is connected
// 
void init() {
		
		openClaw();
		create_full();
}

#endif
