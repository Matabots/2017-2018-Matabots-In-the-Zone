#pragma config(Sensor, dgtl11,  stackEnc,       sensorQuadEncoder)
#pragma config(Motor,  port2,           RMots1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           RMots2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LMots1,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LMots2,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           LiftMots,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           CMot,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port8,           MobMots,       tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "DriveControls.h"

task main() //Boff
{
  setupController();
  while (true)
  {
   	runController();
  }
}
