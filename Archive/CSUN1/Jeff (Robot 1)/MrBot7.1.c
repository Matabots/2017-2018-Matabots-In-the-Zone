#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    ClawLiftAngle,  sensorPotentiometer)
#pragma config(Sensor, dgtl1,  pneuBase,       sensorDigitalOut)
#pragma config(Sensor, dgtl2,  rightEnc,       sensorQuadEncoder)
#pragma config(Sensor, dgtl4,  leftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  leftLiftEnc,    sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  rightLiftEnc,   sensorQuadEncoder)
#pragma config(Sensor, I2C_1,  LMLeftEnc,      sensorNone)
#pragma config(Sensor, I2C_2,  LMRightEnc,     sensorNone)
#pragma config(Sensor, I2C_3,  CMEnc,          sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           CMot,          tmotorVex393_HBridge, openLoop, encoderPort, I2C_3)
#pragma config(Motor,  port2,           RRevs,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LFors,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           RLift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LLift,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RFors,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LRevs,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          CLift,         tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Functions.h"
#include "General Equations.h"
#include "Controls.h"
#include "Vex_Competition_Includes.c"
#include "Teleoperated Control.h"
#include "Robot Definition.h"
#include "autoData.h"
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
	initializeRobot();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

task autonomous()
{
  // Remove this function call once you have "real" code.
  autoGO();

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


task usercontrol()
{
	setupController();
  while (true)
  {
   	runController();
  }
}
