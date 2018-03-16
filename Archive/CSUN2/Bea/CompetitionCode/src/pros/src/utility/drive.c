/**
 * @file: drive.c
 * @created Jan. 26 2017
 * @author Brendan McGuire
 *
 * This file contains instructions for directly manipulating the motors
 */

#include "main.h"
#include "utility/motors.h"

void DriveDirect(int X, int Y, int R) {

  motorSet(DriveFrontLeft,  +Y + X + R);
  motorSet(DriveBackLeft,   +Y - X + R);
  motorSet(DriveFrontRight, -Y + X + R);
  motorSet(DriveBackRight,  -Y - X + R);

}


void DriveHeading(double heading, double speed, int rotation) {
	int X = cos(heading) * speed * 127,
		  Y = sin(heading) * speed * 127,
		  R = rotation;
	DriveDirect(X, Y, R);
}
