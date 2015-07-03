// Created on Wed June 17 2015

#ifndef _ROUTINES_H_
#define _ROUTINES_H_

// Shortcuts
#define ssp(port, pos) set_servo_position(port, pos)
#define cmpc(port) clear_motor_position_counter(port)

// Servos, Motors
#define REVOLVE_MOTOR 1

// Sensors
#define TOPHAT 0

// Misc. Utils
#define TOPHAT_THRESHOLD 800 // Threshold at which dark -> light

#pragma mark - Link Routines

/**
 * Drives to the middle of the field until it sees the black tape.
 * The tophat sensor should be placed on the right-ish.
 * 
 * @param speed The speed at which the robot drives.
 *              Note: recommended speed at ~60
 */
void drive_until_dark(int speed) {
	motor(MOT_LEFT, speed);
	motor(MOT_RIGHT, speed);

	while(analog10(TOPHAT) < TOPHAT_THRESHOLD) {
		msleep(10);
	}
	off(MOT_LEFT);
	off(MOT_RIGHT);
}

#pragma mark - Revolving Tread Functions

void revolve_treads() {

	motor(REVOLVE_MOTOR, 100);

}

#pragma mark - Utility Functions

void init() {

	enable_servos();

}

#endif
