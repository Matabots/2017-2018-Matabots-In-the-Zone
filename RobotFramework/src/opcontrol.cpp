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

//optional or test includes
// #include "../include/utility/drive.h"
// #include "../include/utility/arm.h"
// #include "../include/utility/motors.h"
// #include <iostream>
// #include <string>
//required includes
#include "main.h"
#include "robot.h"
// #include "autonScripts.h"
//#include "../include/uart.h"
//#include "uart.h"

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
 // void i2cTest()
 // {
  //  robot Bot = robot();
  //  i2c iSqC = i2c();

  //  while(true)
  //  {
  //    printf("%d\n", Bot.get_digital()->liftEncoderVal());
  //    delay(50);
  //  }

//



void operatorControl() {
extern robot bot;
// extern TaskHandle callUart;
// taskDelete(callUart);

// taskResume(callUart);
//     lcdInit(uart1);
//     lcdClear(uart1);
  // printf("Ran setup.\n");
  //i2c iSqC = i2c();
  // usartInit(uart1, 9600, SERIAL_DATABITS_8);
  // printf("Created uart.\n");
  //usartInit(uart1, 9600, SERIAL_8N1);
  // char* pntr;
  // pntr = (char*) malloc (sizeof(char)*1);
  // printf("Allocated memory.\n");
  //   lcdInit(uart2);
    // lcdClear(uart2);



  // int count = imeInitializeAll();
  // printf("ime's: %d \n",count);
  // printf("this changed");
  // robot bot = robot();
  // bot.setup();
  // imeReset(0);
  // imeReset(1);
  // imeReset(2);
  // bot.get_digital()->resetLiftEncoders();
  // bot.get_analog()->reset_gyro();
  //
  //
  // delay(1000);
  //runRedNoPreload(bot);
  // runRedNoPreload(bot);
  //delay(1000);
  // runRedNoPreload(bot);
  // delay(1000);
 // bot.set_targetStack(5);
  while(true)
  {
      // printf("leftEnc: %d\n",bot.get_digital()->leftLiftEncoderVal());
      // printf("rightEnc: %d\n",bot.get_digital()->rightLiftEncoderVal());
      // printf("Juke switch: %d\n",bot.get_analog()->get_jukeSwitchVal());
      // printf("gyro: %d\n",bot.get_analog()->gyro_val());
      // printf("limitSwitch: %d\n", bot.get_digital()->get_leftLimitSwitch());
      // // printf("pot: %d\n",bot.get_analog()->get_potentiometerVal());
      // printf("left line sens: %d\n", bot.get_analog()->get_leftLineSensorVal());
      // printf("right line sens: %d\n", bot.get_analog()->get_rightLineSensorVal());
      bot.remoteListen();

      delay(50);
  }

}
