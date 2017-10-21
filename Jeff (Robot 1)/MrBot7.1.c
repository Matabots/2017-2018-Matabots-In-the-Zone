#pragma config(Motor,  port1,           CMot,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port2,           RRevs,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LFors,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port4,           RLift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LLift,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RFors,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LRevs,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          CLift,          tmotorVex393_MC29, openLoop)



#pragma platform(VEX2)
#pragma competitionControl(Competition)
#include "Vex_Competition_Includes.c"
#include "Teleoperated Control.h"
#include "Robot Definition.h"
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
  bStopTasksBetweenModes = true;
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
  // ..........................................................................
  // Insert user code here.
  // ..........................................................................

  // Remove this function call once you have "real" code.
  AutonomousCodePlaceholderForTesting();
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
