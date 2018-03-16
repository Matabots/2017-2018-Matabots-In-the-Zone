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
#include "robot.h"
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

void operatorControl() {
  robot bot = robot();
  bot.setup();


  // motor newMotor = motor(motor2);
  // chassis newChassis = chassis();
  // control* remote = new control();
  // newChassis.addLeftMotor(2, false);
  // newChassis.addRightMotor(3, false);

  // bot.smallLift(100);
  // delay(100);
  // bot.smallLift(-100);
  // delay(100);
  // bot.smallLift(0);

  print("Begin operatorControl()");
    while(1){
      bot.remoteListen();
      printf("%d\n", bot.get_digital()->liftEncoderVal());
      // bot.smallLift();
      // if(remote->absLeftJoystickVal() > 15){
      //   newChassis.leftPower(remote->leftJoystickVal());
      // }else{
      //   newChassis.haltLeft();
      // };
      //
      // if(joystickGetAnalog(1, 2) > 15 || joystickGetAnalog(1, 2) < -15){
      //   newChassis.rightPower(joystickGetAnalog(1, 2));
      // }else{
      //   newChassis.haltRight();
      // };

      // newMotor.set_Power(100);
      // if(joystickGetAnalog(1, 4) > 15){
        // motorSet(motor8, joystickGetAnalog(1, 3));
        // motorSet(motor2, (joystickGetAnalog(1, 3)));
      // }
      // if(joystickGetAnalog(1, 2) > 15){
        // motorSet(motor3, joystickGetAnalog(1, 2) * -1);
        // motorSet(motor9, (joystickGetAnalog(1, 2)));
      // }
      // motorSet(8, 100);
      // printf("%d\n", joystickGetAnalog(1, 1));
    delay(50);
  }

}
