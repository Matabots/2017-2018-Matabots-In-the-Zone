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
//program running on jeff
//Taking drive information from "Teleported Control"
#include "autoDatav2.h"

void resetEnc()
{
	SensorValue[rightEnc] = 0;
	SensorValue[leftEnc] = 0;
}

task main()
{
	resetEnc();
	while(true)
	{
		if (vexRT[Btn8D] == 1)
		{
			//drive forward for 500 degrees using P control
		  float minS = 5;
		  float target = 48;
		  float encAvg = 0;
			float error = target - encAvg;	//error is the difference between the goal and current distance

			float tolerance = 1;	//how accurate do I want the robot to be

			float Kp = 0.9;		//Kp is a multiplier to calibrate the power


			while(abs(error) > tolerance)
			{
				encAvg = ((degToInt(SensorValue[rightEnc]) + degToInt(SensorValue[leftEnc]))/2);
				error = target - encAvg;
				float motSpeed = error * Kp;//constantly updates as I get closer to target

				if (motSpeed < minS)
				{
				  Right(minS);
		  		Left(minS);
				}
			  else
				{
			    Right(motSpeed);
		  		Left(motSpeed);
		    }

				//motor power limits itself to 127 if too large.
				//check to make sure the robot is not stalling before it reaches the target point
					//Note: stalling is either from Kp being too low and doesn't have enough power to push last bit of distance
					//Note: You can eliminate stalling with a minimum speed limit i.e: if(error*kp < MIN){ motor[port[1]] = MIN};

				//*****STEPS TO CALIBRATE Kp*****
				//1. keep increasing Kp until the robot starts to oscillate about the target point physically
				//2. once Kp oscillates, decrease Kp a little so it is stable
		  }
	  	Halt();
			resetEnc();
	  }

		//Things to know about P Controllers
		//
  }

}
