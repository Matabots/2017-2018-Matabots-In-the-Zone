/*
 * @file drive.h
 * @created January 26, 2017
 * @author Brendan McGuire
 *
 *  This header file defines all functions which are related to the drive, like holonomic calculation code, and eventually, drive PID stuff
 */

#include "main.h"

#ifndef INCLUDE_DRIVE_H_
#define INCLUDE_DRIVE_H_

/**
 * Activates the robot to drive in a certain direction
 * @method Drive
 * @param  heading  The heading to travel, in radians
 * @param  speed    The speed to travel at, a number from 0 to 1
 * @param  rotation The rotation to apply, in PWM
 */
void DriveHeading(double heading, double speed, int rotation);

/**
 * Directly drives the robot's drive base
 * @method DriveDirect
 * @param  X           The translation value
 * @param  Y           The forward / backward value
 * @param  R           The rotation to apply, in PWM @TODO: Using a gyroscope, change to radians to rotate
 */
void DriveDirect(int X, int Y, int R);

#endif /* INCLUDE_DRIVE_H_ */
