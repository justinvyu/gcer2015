// Created on Wed June 17 2015

// External
#include "./drive.h"
#include "./generic.h"
#include "./routines.h"

// State
#define s_START 0
#define s_GETFIRSTHALFTRIBBLES 1
#define s_SCOREFIRSTHALF 2
#define s_MOVEUNDERMIDDLE 3
#define s_GETSECONDHALFTRIBBLES 4
#define s_SCORESECONDHALF 5

#define s_END 1337

// Menu
#define MENUSIZE 6
#include "./menu.h"
struct menuitem menu[] = {
	{s_START,"seeding"},
	{s_GETFIRSTHALFTRIBBLES,"get first half"},
	{s_SCOREFIRSTHALF,"score first half"},
	{s_MOVEUNDERMIDDLE,"move under caldera"},
	{s_GETSECONDHALFTRIBBLES,"get second half"},
	{s_SCORESECONDHALF,"score second half"}
};

int main()
{
	
	init();
	Get_Mode();
	start();

	thread revolving_tid = thread_create(revolve_treads);

	while (currstate != s_END) {

		state (s_START) {

			next(s_GETFIRSTHALFTRIBBLES);

		}

		state (s_GETFIRSTHALFTRIBBLES) {

			thread_start(revolving_tid); // Start spinning
			

			next(s_SCOREFIRSTHALF);

		}

		state (s_SCOREFIRSTHALF) {

			next(s_MOVEUNDERMIDDLE);

		}

		state (s_MOVEUNDERMIDDLE) {

			next(s_GETSECONDHALFTRIBBLES);

		}

		state (s_GETSECONDHALFTRIBBLES) {

			next(s_SCORESECONDHALF);

		}

		state (s_SCORESECONDHALF) {

			next(s_END);

		}

	}

	thread_destroy(revolving_tid);
	ao();

}
