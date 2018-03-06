/** @file opcontrol.c
 *  @created January 18, 2017
 *  @author Brendan McGuire
 *  @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "utility/drive.h"
#include "utility/arm.h"
#include "main.h"
#include "utility.h"
#include "utility/motors.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via he Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
// @HACK: Moving these definitions into driver control for now
 void DriveDirect(int X, int Y, int R) {

   motorSet(DriveFrontLeft,  +Y + X + R);
   motorSet(DriveBackLeft,   +Y - X + R);
   motorSet(DriveFrontRight, -Y + X + R);
   motorSet(DriveBackRight,  -Y - X + R);

 };

 int armSpeedMoveUp = 110;
 int armSpeedMoveDown = 70;

 int armSpeedFling = 100;

 void moveArm(int direction, bool fling) {
   if (direction == -1) {
     direction *= armSpeedMoveDown;
   } else {
     if (fling) {
       direction *= armSpeedFling;
     } else {
       direction *= armSpeedMoveUp;
     }
   }

   motorSet(ArmInnerLeft, direction);
   motorSet(ArmInnerRight, -direction);
   motorSet(ArmOuter, -direction);

 }

 void moveClaw(int power) {
     motorSet(Claw, power);
 }


void operatorControl() {

  print("Begin operatorControl()");

	int X, Y, R;
	int armDirection, clawDirection;
	bool fling = false;
	while (1) {

		X = clamp(
			joystickGetAnalog(1, 4),
			40,
			127,
			0,
			127
		);
		Y = clamp(
			joystickGetAnalog(1, 3),
			40,
			127,
			0,
			127
		);
		R = clamp(
			joystickGetAnalog(1, 1),
			40,
			127,
			0,
			127
		);

		// Make rotation slower, we were losing our GOs
		DriveDirect(X, Y, R * 0.9);

		armDirection = joystickGetDigital(1, 6, JOY_UP) ? 1 : joystickGetDigital(1, 6, JOY_DOWN) ? -1 : 0;

		moveArm(armDirection, fling);

    // Claw instructions
    clawDirection = joystickGetDigital(1, 5, JOY_UP) ? 90 : joystickGetDigital(1, 5, JOY_DOWN) ? -90 : 0;

    moveClaw(clawDirection);



  delay(25);
	}
}
