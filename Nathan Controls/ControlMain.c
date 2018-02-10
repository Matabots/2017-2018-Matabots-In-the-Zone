#pragma config(Sensor, dgtl1,  driveEnc,       sensorQuadEncoder)
#pragma config(Motor,  port2,           SMLL,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           SMLR,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           SMRL,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           SMRR,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "MotorSafety.h"
#include "VelocitySpeedControl.h"
task main()
{

	startTask(ControlMonitor);
	MOTOR_PI driveBase;
	motorInit(driveBase, SMLL, driveEnc);
	while(true)
	{
		while(ready == false)
		{}
		motorSpeed = motorSpeed + change;

		motor[SMLL] = motorSpeed;
		motor[SMLR] = motorSpeed;
		motor[SMRL] = motorSpeed;
		motor[SMRR] = motorSpeed;
		wait1Msec(timeSegment);

	}

}
