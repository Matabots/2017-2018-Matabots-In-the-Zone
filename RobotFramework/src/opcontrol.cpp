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
#include "../include/utility/drive.h"
#include "../include/utility/arm.h"
#include "../include/utility/motors.h"
// #include <iostream>
// #include <string>
//required includes
#include "main.h"
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
  //   lcdInit(uart2);
    // lcdClear(uart2);

  int count = imeInitializeAll();
  printf("ime's: %d \n",count);
  robot bot = robot();
  bot.setup();
  imeReset(0);
  imeReset(1);
/*  i2c iSqC = i2c();
  usartInit(uart1, 9600, SERIAL_DATABITS_8);
  char* pntr;
  pntr = (char*) malloc (sizeof(char)*1);*/
  // std::string sauce = "";


  //bot.smallLift(100);
  //delay(100);
  //bot.smallLift(-100);
  //delay(100);
  //bot.smallLift(0);
  //use millis() for integrated timing

  printf("Begin operatorControl\n");
  // //int motor_velocity = 0;

  bot.get_digital()->resetLiftEncoders();
  while(true){
      printf("left: %d\n",bot.get_digital()->leftLiftEncoderVal());
      printf("right: %d\n",bot.get_digital()->rightLiftEncoderVal());
      bot.get_arm()->primaryLiftPosition(5, bot.get_digital()->leftLiftEncoderVal());
      delay(50);
    }
////////////////////////////////////////////////////////////////////////////////////////////////
  // int motVel;
  // int timer = millis();
  // CartesianVector tP;
  // tP.x = 26;
  // tP.y = 0;
  // bot.get_drive()->generatePathTo(tP);
  // int wpNum = 0;
///////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////
// bool waypointComplete = false;
  // while(!waypointComplete)
  // {
  //   // if(abs(bot.get_drive()->getLeftMotorAt(0)->get_posPID()->get_error()) > bot.get_drive()->getLeftMotorAt(0)->get_posPID()->get_deadband()){
  //   //   timer = millis();
  //   // // }
  //   bot.get_drive()->leftPosition(50);
  //   bot.get_drive()->rightPosition(50);
  //   printf("ticks: %f\n", bot.get_drive()->get_currPos().x);
  //   // bot.get_drive()->get_waypoints()->printWaypoints();
  //   // //bot.get_drive()->leftPower(30);
  //   //   if(abs(bot.get_drive()->getLeftMotorAt(0)->get_posPID()->get_error()) < bot.get_drive()->getLeftMotorAt(0)->get_posPID()->get_deadband() )//&& millis() - timer > 100)//operatingTime.GetTicks() < 10000)
  //   //   {
  //   //     wpNum++;
  //       if(abs(20-bot.get_drive()->get_currPos().x) < 3 ){
  //         waypointComplete = true;
  //       }
  //   //   }
  //    bot.get_drive()->updatePos();
  //   delay(50);
  // }
  // bot.get_drive()->leftPower(0);
  // bot.get_drive()->rightPower(0);
  //////////////////////////////////////////////////////////////////////////////////////

//  bot.get_drive()->rightPower(0);
//  bot.get_drive()->leftPower(0);

  // while(true){
  //   bot.remoteListen();
  //
  //   delay(50);
  // }

    // while(true)
    // {
      // printf("%d\n",iSqc.read();
      //bot.get_drive()->rightVelocity(50); FUCK VELOCITY CONTROL UNTIL I GET TIME
      //bot.get_drive()->leftVelocity(50);
      //motorSet(motor8,80);
      //motorSet(motor9,-80);
      //bot.get_drive()->leftPosition(10); //drive forward for 10 inches

////////////////// UART //////////////////////////////////////////////////////////////
  /*    fread(pntr,sizeof(char),1,uart1);

      // for(x=0;x<3;x++){
        printf("%c\n", pntr[0]);
      // };
if (pntr[0] == '&')
{
  //std::cout << sauce << '\n';
  // sauce = "";
}
else
{
  //sauce += pntr[0];
  //pntr[0] = '';
}
*/
////////////////////////////////////////////////////////////////////////////////////////




  // printf("The Program has Ended\n");

}
