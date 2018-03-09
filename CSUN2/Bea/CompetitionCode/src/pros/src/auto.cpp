/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "utility/drive.h"
#include "utility/motors.h"
#include "utility/vector.h"
#include "utility/arm.h"
#include "utility/units.h"
#include <API.h>
// #include "robot.h"
// #include "chassis.h"
#include "robot.h"
#include "analogSensors.h"
#include "digitalSensors.h"
#include "chassis.h"
#include "lift.h"
#include "control.h"
#include "claw.h"
#include "i2c.h"
#include <vector>
#include "motor.h"
#include "ports.h"
#include "potentiometer.h"

// #include "motor.h"
#define degreesToRadians(angleDegrees) (angleDegrees * PI / 180.0)
#define radiansToDegrees(angleRadians) (angleRadians * 180.0 / PI)

/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost,  the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it left off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */

void autonomous() {
    //declare a robot and setup the ports
    robot bot = robot();
    bot.setup();
    // bot.joystickInputs();
    //some testing of classes
    // chassis drive = chassis();
    // drive.addLeftMotor(motor2, false);
    // bot.get_drive()->addLeftMotor(motor2, false);
    // robot bot2 = robot();
    // bot2.get_drive()->addRightMotor(motor3, true);
    // delay(400);


}
