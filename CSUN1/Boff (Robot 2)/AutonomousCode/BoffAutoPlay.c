#pragma config(Sensor, in1,    Gyro,           sensorGyro)
#pragma config(Sensor, in8,    Potent,         sensorPotentiometer)
#pragma config(Sensor, dgtl1,   LED1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,   LED1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,   LED1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,   LED1,           sensorLEDtoVCC)
#pragma config(Sensor, dgtl5,  LimL1,          sensorTouch)
#pragma config(Sensor, dgtl6,  LimR1,          sensorTouch)
#pragma config(Sensor, dgtl7,  LEnc,           sensorQuadEncoder)
#pragma config(Sensor, dgtl9,  REnc,           sensorQuadEncoder)
#pragma config(Sensor, dgtl11, stackEnc,       sensorQuadEncoder)
#pragma config(Motor,  port1,           CMot,          tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           LMots1,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           LMots2,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LMots3,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           MobMots1,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           RMots1,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RMots2,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           RMots3,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           MobMots2,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LiftMot,       tmotorVex393_HBridge, openLoop)

#include "AutonFunctions.h"
#include "v2DriveControlsCopy.h"
float GyroDisplay; //temporary
void resetEnc()
{
	SensorValue[stackEnc] = 0;
}
task runGyroControl()
{
	while(true)
	{
		moveGyro();
	}
}

task runLiftControl()
{
	while (true)
	{
		MoveArm();
	}
}

task main()
{
	SetupSens();
	resetEnc();
	startTask(runGyroControl);
	startTask(runLiftControl);

		autonGo();

}
