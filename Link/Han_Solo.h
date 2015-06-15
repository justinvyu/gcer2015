// Created on Thu June 11 2015

// Replace FILE with your file's name
#ifndef _FILE_H_
#define _FILE_H_
#define MOT_LEFT 0//Sam edition!
#define MOT_RIGHT 3
#define MOT_MID 2
#define PI 3.14159265358979
#define SPD 1000
#define SPDl 1000.
#define SPDr 948. 
#define SPDm 1000
#define rdistmult (SPDr/SPDl)

#define ks 13.1//distance from one wheel to another in cm
#define wheeldiameter 4 //this is in cm

#define CMtoBEMF (921/wheeldiameter/PI) //921 is how many backemf ticks there are in a full wheel, take the number of units per rotation, divide by circumference
#define LBUMP digital(14)
#define RBUMP digital(15) //left/right back bump sensors (used for square_back())


#define drive_off() off(MOT_RIGHT) ;off(MOT_LEFT)
#define drive(mL,mR); {mav(MOT_LEFT,(mL)*10);mav(MOT_RIGHT,(mR)*10);}


void solo_forward(float distance){//go forward a number of CM    NOT    backEMF counts
	if(distance < 0l){
		distance = -distance;
	}
	long newdist;
	newdist = distance*CMtoBEMF;//conversion ratio
	mrp(MOT_MID, SPDm, newdist);
	bmd(MOT_MID);
}


#endif
