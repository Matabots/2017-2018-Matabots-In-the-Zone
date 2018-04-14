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

  int count = imeInitializeAll();
  printf("ime's: %d \n",count);
  printf("this changed");
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

  // printf("Begin operatorControl\n");
  // //int motor_velocity = 0;
// //////////////////////////////////////////////////////////////////////////////////////////////
  bot.get_digital()->resetLiftEncoders();
  while(true){
      printf("left: %d\n",bot.get_digital()->leftLiftEncoderVal());
      printf("cones: %d\n",bot.get_stackedCones());
      printf("targetCones: %d\n",bot.get_targetStack());
      printf("right: %d\n",bot.get_digital()->rightLiftEncoderVal());
      printf("pot: %d\n",bot.get_analog()->get_potentiometerVal());
      printState(bot.get_state());
      bot.remoteListen();
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

 // botUart* botUart1 = new botUart();

  // while(true)//operatingTime.GetTicks() < 10000)
  // {
  //   // botUart1.readData();
  //
  //   // printf("%c\n", 's');
    // botUart1->runUART();
    // botUart1->readData();
    // //botUart1->printStr();
    // botUart1->setObVals();
    // botUart1->printObVals();
    // while(true)
    // {
      // printf("%d\n",iSqc.read();
      // fread(pntr,sizeof(char),1,uart1);
      //fgets(pntr,sizeof(char),1,uart1);
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
>>>>>>> 951d77628b906356d2b5c6d0a113c54c66f16603

      // for(x=0;x<3;x++){
        // printf("%c\n", pntr[0]);
      // };
<<<<<<< HEAD
      // if (pntr[0] == '&')
      // {
      //   //std::cout << sauce << '\n';
      //   // sauce = "";
      // }
      // else
      // {
      //   //sauce += pntr[0];
      //   //pntr[0] = '';
      // }
      //iSqC.read();
      delay(25);
    // }
  //   bot.get_drive()->leftPower(127);
  //   bot.get_drive()->rightPower(127);
  //
  //   motVel =  bot.get_drive()->getLeftMotorAt(0).get_velocity(bot.get_digital()->leftEncoderVal());
  //   lcdPrint(uart1, 2, "Vel: %d",motVel );//;

    //printf("Inches: %d \n",(int)abs(ticksToInches(bot.get_digital()->get_RightEncoder(),bot.get_drive()->get_wheelDiameter())));
    //printf("Ticks: %d \n",(int)abs(bot.get_digital()->leftEncoderVal()));
    //bot.remoteListen();
    // printf("%d\n", bot.get_digital()->liftEncoderVal());

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
  //   delay(25);
  }
=======
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
