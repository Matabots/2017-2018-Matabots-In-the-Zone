/*
  Commands list
*/
#include "Variables.h"
#include "AutonRun.h"
#include "robotSetup.h"
/*
	 (rMotors).frontRight = REdgeMots;
   (rMotors).rearRight = RInsideMots;
   (rMotors).frontLeft = LEdgeMots;
   (rMotors).rearLeft = LInsideMots;
   (rMotors).lift1 = LiftMotor1;
   (rMotors).lift2 = LiftMotor2;
   (rMotors).smallLift1 = ConeLift;
   (rMotors).ef = Claw;
*/
void tasksFinished()
{
	while(!atGyro)
	{
	}
}

//moves the cone lift arm to a darget degree
// 0<targetDeg<600
void MoveConeLift(int speed, int targetDeg)// to targetDeg at speed
{
	minS = 20;
	while(SensorValue[robot.dSensors->coneLiftEnc] < targetDeg)
	{
		    smallLift(speed);
	}
	smallLift(0);
}
void AutoLift()
{
	float oldDeg;
	{
	  switch ( currentStack )
	 	{
		case 0:
		  oldDeg = targetDeg;

		  controlClaw(1);

	    targetDeg = firstCone;
			wait10Msec(165);

	    controlClaw(0);
	    wait10Msec(20);

			targetDeg = oldDeg;
			same = false;// goes back to old position

			break;

		case 1:
		  oldDeg = targetDeg;

		  controlClaw(1);

	    targetDeg = secondCone;
			wait10Msec(150);

	    controlClaw(0);
	    wait10Msec(50);

			targetDeg = oldDeg;
			break;

		case 2:
		  oldDeg = targetDeg;

		  controlClaw(1);

	    targetDeg = thirdCone;
			wait10Msec(130);

	    controlClaw(0);
	    wait10Msec(50);

			targetDeg = oldDeg;
			break;
	  }
	  currentStack++;
  }
}
void StackGro()
{
  targetDeg = -138;
}
void StackLoad()
{
	targetDeg = -80;
}
void StackNeut()
{
	targetDeg = 0;
	currentStack = 0;
}


//-----------------------------------GyroScope
float degToIn(float deg)
{
	return ((deg * (3.14 * 4))/360);
}


void moveGyro(int targetGyro)
{
  int tolerance = 8;//7
	float KpT = 0.85;// was 0.8
	float difference = (targetGyro - SensorValue[robot.aSensors->gyroscope]);

		time1[T1] =0;
		while(abs(difference) > tolerance)// || time1[T1] > 500)
		{
			  difference = (targetGyro - SensorValue[robot.aSensors->gyroscope]);
        //calculate to see if it is faster to turn left or right
        if(difference > 180)
        {
                difference -= 360;
        }
        if(difference < -180)
        {
                difference += 360;
        }
        if(abs(difference)>tolerance)
        {
        	time1[T1] =0;
        }
        int power = difference * KpT;

        power = power < -100 ? -100 : power;
        power = power > 100 ? 100 : power;
        if(power < 0 && power > -25)
        {
        	power = -25*KpT;
        }
        if(power > 0 && power<25)
        {
        	power = 25*KpT;
      	}

        motor[robot.rMotors->frontLeft] = -power;
        motor[robot.rMotors->rearLeft] = -power;


        motor[robot.rMotors->frontRight] = -power;
        motor[robot.rMotors->rearRight] = power;
        delay(10);
		}
		atGyro = true;
}

void PIDDrive(float targetIn) //using drive to? not continuous
{
	resetChassisEnc();
	minGo = 9;
	errorD = targetIn + degToIn(SensorValue[robot.dSensors->leftEncoder];	//error is the difference between the goal and current distance

	toleranceD =3.7; //3.7;	//how accurate do I want the robot to be was at .25
  kp2 = 4.1;
	totalErrorD = 0;
	ki2 = 0;
	kd2 = 0;
	time1[T3] = 0;
	float dSpeed =0;
	SensorValue[REnc]=0;
	float gyroOrig = gyroVal;
	float gyroCorr = 3;//3.5
	while(abs(errorD) > toleranceD || (time1[T3] < 1000))
		{
			//SensorValue[(tSensors) 10 ] = 1;
			//encAvg = (((SensorValue[REnc]) + (SensorValue[LEnc]))/2);
			errorD = targetIn + degToIn(SensorValue[robot.dSensors->leftEncoder]);
		  dSpeed = errorD * kp2;// + (totalErrorD * ki2) + ((errorD - prevErrorD) * kd2)) ;//constantly updates as I get closer to target

		  if (abs(dSpeed) < minGo)
			{
				 dSpeed = dSpeed/abs(dSpeed);
			   Right((minGo*dSpeed)+(gyroOrig-gyroVal)*gyroCorr);
			   Left((minGo*dSpeed)-(gyroOrig-gyroVal)*gyroCorr);
			}
		  else
		  {
		  		Right(dSpeed+(gyroOrig-gyroVal)*gyroCorr);
			    Left(dSpeed-(gyroOrig-gyroVal)*gyroCorr);
		  }
			//if(abs(errorD) < toleranceD*50)
			//{
			//		//kD = 20;
			//	//	ki = 1;
			//}
			if(abs(errorD) > toleranceD)
			{
		 		time1[T3] = 0;
			}
		}
	left(0);
	right(0);
	  //}

		//Things to know about P Controllers
		//
}
void DriveIn(int leftPower, int rightPower, int deg)
{
}



//------------------Mobile Goal Lift --------------
void AutonGoalLiftMovement(int moveUp){// -1 moves the arm down
	while(moveUp == 1 && abs(SensorValue[robot.dSensors->LiftEnc]) > robot.goalLiftLimitUp){
		motor[robot.rMotors->lift1] = 127;
		motor[robot.rMotors->lift2] = -127;
	}while(moveUp == -1 && abs(SensorValue[robot.dSensors->LiftEnc]) < robot.goalLiftLimitDown){
		motor[robot.rMotors->lift1] = -127;
		motor[robot.rMotors->lift2] = 127;
		robot.goalLiftLimitUp = 5;
	}
		motor[robot.rMotors->lift1] = 0;
		motor[robot.rMotors->lift2] = 0;
}


void tinyLiftDown(float time)
{
	timeVal = time;
  mobDown = true;
  wait10Msec(40);
}
void tinyLiftUp()
{
  mobUp = true;
  wait10Msec(40);
}
void tinyLiftUpTmp(float time)
{
	motor[robot.rMotors->lift1] = 127;
	motor[robot.rMotors->lift2] = 127;

	wait10Msec(time * 100);

	motor[robot.rMotors->lift1] = 0;
	motor[robot.rMotors->lift2] = 0;

}

void checkMobile()
{
  if (mobUp)
  {
  	while(SensorValue[robot.dSensors->coneLiftEnc] < 20)	//MEASURE ACTUAL VALUE
	  {
      motor[robot.rMotors->lift1] = -127;
      motor[robot.rMotors->lift2] = -127;
    }
    motor[robot.rMotors->lift1] = 0;
	  motor[robot.rMotors->lift2] = 0;
  }
  else if (mobDown)
  {
    motor[robot.rMotors->lift1] = 127;
    motor[robot.rMotors->lift2] = 127;

	  wait10Msec(timeVal * 100);

	  motor[robot.rMotors->lift1] = 0;
	  motor[robot.rMotors->lift2] = 0;
  }
  mobUp = false;
  mobDown = false;
}

void score(float leftP, float rightP, float sec)
{
	time1[T2] = 0;
	while (time1[T2] < (sec * 1000))
	{
  	Right(rightP);
	  Left(leftP);
	}

	left(0);
	right(0);
}
void driveBack(float leftP, float rightP, float sec)
{
	time1[T2] = 0;
	while (time1[T2] < (sec * 1000))
	{
  	Right(-leftP);
	  Left(-rightP);
	}

	left(0);
	right(0);
}

void moveDeg(int leftPower, int rightPower, int deg)
{
	resetChassisEnc();

	while(abs(SensorValue[robot.dSensors->leftEncoder])<deg && abs(SensorValue[robot.dSensors->rightEncoder])<deg)
	{
			left(leftPower);
      right(rightPower);
  }
     left(0);
      right(0);

}

void PreLoad()
{
  motor[robot.rMotors->ef] = 30;
  //delay lift
  wait10Msec(50);
  targetDeg = 0;
}
