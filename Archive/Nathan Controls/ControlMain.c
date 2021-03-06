#pragma config(Sensor, dgtl11, driveEnc,       sensorQuadEncoder)
#pragma config(Motor,  port1,           MobMots1,      tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LMots1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LMots2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LMots3,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LMots4,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RMots1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RMots2,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           RMots3,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           RMots4,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          MobMots2,      tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "MotorSafety.h"
#include "VelocitySpeedControl.h"
task main()
{

	startTask(ControlMonitor);
	MOTOR_PI driveBase1;
	MOTOR_PI driveBase2;
	MOTOR_PI driveBase3;
	MOTOR_PI driveBase4;
	motorInit(driveBase1, LMots1, driveEnc);
	motorInit(driveBase2, LMots2, driveEnc);
	motorInit(driveBase3, LMots3, driveEnc);
	motorInit(driveBase4, LMots4, driveEnc);
	driveBase1.speedSet = 100;
	driveBase2.speedSet = 100;
	driveBase3.speedSet = 100;
	driveBase4.speedSet = 100;
	time1[T1] = 0;
	time1[T2] = 0;
	while(true)
	{
	//	motorSpeed = motorSpeed + change;

	driveBase1.speedSet = 100;
	driveBase2.speedSet = 100;
	driveBase3.speedSet = 100;
	driveBase4.speedSet = 100;
		PI_Control(driveBase1);
		PI_Control(driveBase2);
		PI_Control(driveBase3);
		PI_Control(driveBase4);

		// Start a group of datalog values
		datalogDataGroupStart();

		// Add the value 27 to datalog series 0
		datalogAddValue(1, driveBase1.speedSet);
		datalogAddValue(2, driveBase1.lastEncoderRead);
		datalogAddValue(3, driveBase1.speedRead);
		datalogAddValue(4, driveBase1.controller_output);
		// End a group of datalog values
		datalogDataGroupEnd();

		wait1Msec(timeSegment);
	}

}
