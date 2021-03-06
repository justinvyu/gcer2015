// Created on Wed June 10 2015

// Replace FILE with your file's name
#ifndef _ROUTINES_H_
#define _ROUTINES_H_

// Shortcuts
#define ssp(servo, position) set_servo_position(servo, position)
#define mm(inch) inch * 25.4
#define cmpc(port) clear_motor_position_counter(port)

// Servos, Motors
#define ARM_MOTOR 0

#define EXTENSION_SERVO 1

// Sensors
#define TOUCH 11
#define SQUARE_TOUCH 15
#define CONFIRM_LEVER 12
#define RIGHT_TOPHAT 2
#define LIGHT_SENS 0

// Misc. Utils
#define ARM_DOWN_POSITION 5050
#define TOPHAT_THRESH 300
#define CUBE_SERVO 3
#define CUBE_CLOSED 1900
#define CUBE_OPEN 960

#define EXTENSION_EXTENDED 950
#define EXTENSION_RETRACTED 1785

#pragma mark - Create Routines

void create_forward_until_touch(int rspeed, int lspeed) { // Allows for slight curvature

	create_drive_direct(rspeed, lspeed);
	while(get_create_lbump() == 0 || get_create_rbump() == 0) {
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

void create_square() {

	float st = curr_time();
	create_drive_direct(-150, -150);
	while(digital(SQUARE_TOUCH) == 0 || (curr_time() - st) < 5.0) {
		msleep(10);
	}
	create_stop();
	create_backward(mm(2), 150);
	create_block();

}

void create_backward_until_tophat() {
		create_drive_direct(-150, -150);
		while(analog10(RIGHT_TOPHAT) < TOPHAT_THRESH) {
			msleep(10);
		}
		create_stop();

}

#pragma mark - Arm Routines

void raise_arm_full() {

	motor(ARM_MOTOR, -100);		 // Raise
	while(digital(TOUCH) == 0) { // Wait for touch
		msleep(10);
	}
	off(ARM_MOTOR);

}

void raise_arm(float time) {

	motor(ARM_MOTOR, -100);
	msleep(time);
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

#pragma mark - Extension Functions

void extendExtension() {

	//servo_set(EXTENSION_SERVO, EXTENSION_EXTENDED, 1);
	ssp(EXTENSION_SERVO, EXTENSION_EXTENDED);
	msleep(200);

}

void retractExtension() {

	servo_set(EXTENSION_SERVO, EXTENSION_RETRACTED, 1);
	msleep(200);

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
		ssp(EXTENSION_SERVO, EXTENSION_RETRACTED);
		create_full();
}

#endif
