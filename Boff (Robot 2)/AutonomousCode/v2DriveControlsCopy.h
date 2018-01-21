/*
Drive Functions (some code taken from Jeff (Robot 1)/Teleoperated Control.h"
Version 2 (added PID controlled lift)
@@@@This copy has been modified to accommodate start with 116ish degree offset
*/
//drive stalls when lift hits an obstacle

int lastPost = 0;
int n =  1;
float minS;
float minGo;
float minTurn;
float maxTurn;
float target;
float target2;
float enc = 0;
float encAvg = 0;
float startOff = 140;
float pitch;
float error;	//error is the difference between the goal and current distance
float error2;
float tolerance;//how accurate do I want the robot to be
float tolerance2;
float kp; //Kp is a multiplier to calibrate the power
float kp2;
float totalError;
float totalError2;
float ki;
float ki2; // for drive
float kd = 0;
float kd2 = 0;
float targetDeg;
float deltaGyro;
float gyroVal;
float targetGyro;


bool atGyro = false;
bool atAngle = false;
bool cone = false;
bool same;
bool opened = false;
bool noNew;
#define DEADZONE 15
int potentVal = 0;

struct Controller
{
	TVexJoysticks stack;
	TVexJoysticks stackUp;
	TVexJoysticks GroLift;
	TVexJoysticks autoLLift;
	TVexJoysticks rightMotors;
	TVexJoysticks	leftMotors;
	TVexJoysticks	clawOpen;
	TVexJoysticks clawClose;
	TVexJoysticks goalLiftU;
	TVexJoysticks goalLiftD;
	TVexJoysticks resStackNeut;
	TVexJoysticks coneBool;
};

Controller controller;

void tasksFinished()
{
	while(!atGyro || !atAngle)
	{
	}
}
void setupController()
{
	controller.GroLift = Btn7D; //ground collector position
	controller.autoLLift = Btn7L; //autoload position
	controller.stack = Btn8R; //activate stacker
	controller.stackUp = Btn8L;
	controller.rightMotors = Ch2;	//move the right side of the robot
	controller.leftMotors = Ch3;	//move the left side of the robot
	controller.clawOpen = Btn5D;	//open claw
	controller.clawClose = Btn5U;	//close claw
	controller.goalLiftU = Btn6U; //lift  the goal
	controller.goalLiftD = Btn6D; //lower the goal
	controller.resStackNeut = Btn7U; //reset stack # and set lift to neut
	controller.coneBool = Btn8D;
}
int currentStack = 0;

void resetVals()
{
	minGo = 0;
	target2 = 0;
	encAvg = 0;
	error2 = 0;
	tolerance2 = 0;
	totalError2 = 0;
	kp2 = 0;
	ki2 = 0;
	kd2 = 0;
}

void reSetDEnc()
{
	SensorValue[LEnc] = 0;
	SensorValue[REnc] = 0;
}
void MoveArmTo(float input)
{
	targetDeg = input;
}

void MoveArm()
{
	atAngle = false;
	minS = 20;
	pitch = SensorValue[stackEnc] + startOff;
	error = targetDeg - pitch;	//error is the difference between the goal and current distance

	tolerance = 15;	//how accurate do I want the robot to be was at .25
  if (cone) {
  	kd = 100;
    kp = 1.8;
    minS = 30;
    tolerance = 8;
  } else  {
	  kp = 1.3;		//Kp is a multiplier to calibrate the power //1.3 works
  }
  if (targetDeg == 0) {
  	minS = 10;
  	tolerance = 15;
  	kp = 1.5; //1.7;
  }
  if (currentStack == 1) {
    kp = 1.7;
  }
	totalError= 0;
	ki = 0;

	float prevError = 0;
	float kD = 0;
	time1[T1] = 0;

	while(abs(error) > tolerance )//|| time1[T1] > 500)
		{
			pitch = SensorValue[stackEnc] + startOff;
			error = targetDeg - pitch;
			float motSpeed;
			if (target == 0)
		  {
		    motSpeed = -((error * kp) + (totalError * ki) + ((error - prevError) * kD)) ;//constantly updates as I get closer to target
		  } else {
			  motSpeed = -((error * kp) + (totalError * ki) + ((error - prevError) * kD)) ;//constantly updates as I get closer to target
		  }
			if (abs(motSpeed) < minS)
			{
			  if (motSpeed < 0) {
			    motor[LiftMot] = -minS;
			  } else {
			    motor[LiftMot] = minS;
			  }
			}
		  else
		  {

		  		motor[LiftMot] = motSpeed;

		  }
			if(abs(error) < tolerance*50)
			{
					//kD = 20;
				//	ki = 1;
			}
			if(abs(error)>tolerance)
			{
		 		time1[T1] = 0;
			}
				//motor power limits itself to 127 if too large.
				//check to make sure the robot is not stalling before it reaches the target point
					//Note: stalling is either from Kp being too low and doesn't have enough power to push last bit of distance
					//Note: You can eliminate stalling with a minimum speed limit i.e: if(error*kp < MIN){ motor[port[1]] = MIN};

				//*****STEPS TO CALIBRATE Kp*****
				//1. keep increasing Kp until the robot starts to oscillate about the target point physically
				//2. once Kp oscillates, decrease Kp a little so it is stable
		  totalError += error;
		  prevError = error;

		}
	  //}

		//Things to know about P Controllers
		//
		lastPost = target;
		atAngle = true;
}

void MoveClaw()
{
	if(!opened && (SensorValue[Potent] > potentVal - 200)) //&& abs(SensorValue[CMEnc]) < 90)
	{ //open
		motor[CMot] = -127;
  }
  else if(opened && (SensorValue[Potent] < (potentVal + 1000))) //&& abs(SensorValue[CMEnc]) > 0)
  { //close
    motor[CMot] = 127;
  }
  else
  {
  	motor[CMot] = 0;
  }
}

void AutoClaw(int IO) //0 is open, 1 is closed
{
	//open claw
	switch(IO)
	{
  case 0:
    time1[T1] = 0;
    while((SensorValue[Potent] > potentVal - 300) && (time1[T1] < 3000))
	  {
		  motor[CMot] = -127;
	  }
    motor[CMot] = -20;
    wait10Msec(100);
    cone = false;
  	break;

  case 1:

    cone = true;
    motor[CMot] = 30;
    /* //old code to close. We now close manualy
    time1[T1] = 0;
    while((SensorValue[Potent] < potentVal + 850) && (time1[T1] < 3000))//&& abs(SensorValue[CMEnc]) > 0)
    { //close
      motor[CMot] = -127;
    }
    motor[CMot] = -20;
    wait10Msec(100);
    cone = true;
    */
  	break;
  }
}


void AutoLift()
{
	float oldDeg;
	 switch ( currentStack )
	 	{
		case 0:
		  oldDeg = targetDeg;

		  AutoClaw(1);

	    targetDeg = 80;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			targetDeg = oldDeg;
			same = false;// goes back to old position

		  /*old code with currentDeg starting at 0. We added a reset to old Position and took off claw closure
		  currentDeg = -138;
		  wait10Msec(300);

		  AutoClaw(1);

	    currentDeg = 85;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			currentDeg = 0; // parameter will be "lastPos"
			*/
			break;

		case 1:
		  oldDeg = targetDeg;

		  AutoClaw(1);

	    targetDeg = 80;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			targetDeg = oldDeg;
			break;

		case 2:
		  oldDeg = targetDeg;

		  AutoClaw(1);

	    targetDeg = 60;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			targetDeg = oldDeg;
			break;
	  }
	  currentStack++;
}

void clawPow()
{
	if (vexRT[controller.coneBool] == 1 && cone == false) {
		cone = true;
		wait10Msec(50);
	}
	if (cone)
	{
	  motor[CMot] = 30;
	  if (vexRT[controller.coneBool] == 1) {
	    cone = false;
	    wait10Msec(50);
	  }
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////

float degToInt(float deg)
{
	return ((deg * (3.14 * 4))/360);
}

void reSetGyro() // probably not needed
{
  SensorValue[Gyro] = 0;
}

void Right(int speed)
{
	motor[RMots1] = speed;
  motor[RMots2] = speed;
	motor[RMots3] = speed;
}
void Left(int speed)
{
	motor[LMots1] = speed;
	motor[LMots2] = speed;
	motor[LMots3] = speed;
}
void Halt()
{
	Right(0);
	Left(0);
}

void GyroCalibrate()
{
 //calibrate
 /*SensorType[Gyro] = sensorNone;
 wait1Msec(100);
 //Reconfigure Analog Port 8 as a Gyro sensor and allow time for ROBOTC to calibrate it
 SensorType[Gyro] = sensorGyro;
 wait1Msec(2000);

//Adjust SensorScale to correct the scaling for your gyro
 SensorScale[in1] = 260;
 //Adjust SensorFullCount to set the "rollover" point. 3600 sets the rollover point to +/-3600
 SensorFullCount[in1] = 3600;*/
 SensorValue[Gyro]=0;
	float prevGyro;
	time1[T1] = 0;
  while(time1[T1] < 2000)
  {
	  Halt();
		prevGyro = gyroVal;
		wait1Msec(10);
		gyroVal = SensorValue[Gyro];
		deltaGyro = (gyroVal - prevGyro);
	}
}

void SetupSens()
{
	GyroCalibrate();
	targetDeg = 0; //PID arm setup to neutral
	SensorValue[LEnc] = 0; //may affect lift , unsure
	SensorValue[REnc] = 0;
	reSetGyro();
	targetGyro = 0;
  SensorValue[stackEnc] = 0; //may affect lift enc, unsure
  potentVal = SensorValue[Potent];
  Halt();
}

void GyroUpdate()
{
	gyroVal = ((SensorValue[Gyro]) - deltaGyro)/10; //used instead of gyroVal
}

void moveGyro()
{
	atGyro = false;
  int tolerance = 7;
	float KpT = 0.8;
	GyroUpdate();
	float difference = (targetGyro - gyroVal);

		time1[T1] =0;
		while(abs(difference) > tolerance)// || time1[T1] > 500)
		{
				GyroUpdate();
			  difference = (targetGyro - gyroVal);
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

        motor[LMots1] = -power;
        motor[LMots2] = -power;
        motor[LMots3] = -power;

        motor[RMots1] = power;
        motor[RMots2] = power;
        motor[RMots3] = power;
        delay(10);
		}
		atGyro = true;
}


/* cancelled, instead using gyroPID for a continuous PID
void turnRight(int degree)
{
	reSetDEnc();


	minGo = 5;
	target2 = degree;
	encAvg = 0;
  error2 = target2 - encAvg;

  tolerance2 = 0.5;	//how accurate do I want the robot to be was at
  kp2 = 1;
	totalError2 = 0;
	ki2 = 0;

	float prevError2 = 0;
  int inch = (((7.5 * 3.14) * degree)/180);  //
	while (abs(degToInt(SensorValue[LEnc])) < inch && abs(degToInt(SensorValue[REnc])) < inch && abs(gyroVal) < degree)
	{
		float dSpeed = ((error2 * Kp2) + (totalError2 * ki2) + ((error2 - prevError2) * kd2)) ;//constantly updates as I get closer to target
		if (dSpeed < minS)
		{
			Right(-minS);
    	Left(minS);
    }
    else
    {
    	Right(-dSpeed);
    	Left(dSpeed);
    }

    totalError2 += error2;
		prevError2 = error2;

  }
  Halt();
}
void turnLeft(int degree, int power)
{
	reSetGyro();
	reSetDEnc();

  minGo = 5;
	target2 = degree;
	encAvg = 0;
  error2 = target2 - encAvg;
	tolerance2 = 1;
	kp2 = 0.9;

	float prevError2 = 0;
  int inch = (((7.5 * 3.14) * degree)/180); //
	while (abs(degToInt(SensorValue[LEnc])) < inch && abs(degToInt(SensorValue[REnc])) < inch && abs(gyroVal) < degree)
	{
		float dSpeed = ((error2 * Kp2) + (totalError2 * ki2) + ((error2 - prevError2) * kd2)) ;//constantly updates as I get closer to target

		if (abs(dSpeed) < minGo)
			{
			   Right(minGo);
			   Left(-minGo);
			}
		  else
		  {
		  		Right(dSpeed);
			    Left(-dSpeed);
		  }
			if(abs(error2) < tolerance2*50)
			{
					//kD = 20;
				//	ki = 1;
			}
			if(abs(error2) > tolerance2)
			{
		 		time1[T3] = 0;
			}

  	totalError2 += error2;
		prevError2 = error2;
  }
  Halt();
}
*/

void moveInchTwo(int power, int inch)
{
  reSetDEnc();

	while (abs(degToInt(SensorValue[LEnc])) < inch && abs(degToInt(SensorValue[REnc])) < inch)
	{
		Right(power);
  	Left(power);
  }
  Halt();
}
void MoveClawTwo() //copied from drive, then modified
{

	if(!opened) //&& abs(SensorValue[CMEnc]) < 90)
	{
		motor[CMot] = 127;
		opened = true;
		wait10Msec(100);
  }
  else if(opened) //&& abs(SensorValue[CMEnc]) > 0)
  {
    motor[CMot] = -127;
    opened = false;
    wait10Msec(100);
  }
  else
  {
  	motor[CMot] = 0;
  }
}
void tinyLiftUp()
{
	while(SensorValue[LimL1] == 0 && SensorValue[LimR1] == 0)
	{
    motor[MobMots1] = -127;
    motor[MobMots2] = -127;
  }
  motor[MobMots1] = 0;
	motor[MobMots2] = 0;

}

void tinyLiftDown(int time)
{
	motor[MobMots1] = 127;
  motor[MobMots2] = 127;

	wait10Msec(time);

	motor[MobMots1] = 0;
	motor[MobMots2] = 0;
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
void TurnTo(float input)
{
	targetGyro = input;
}
/* if(vexRT[controller.stackUp])
	{
		currentStack = currentStack + 1;
	}
*/
void PIDDrive(float input) //using drive to? not continuous
{
	reSetDEnc();
	minGo = 5;
	target2 = input;
	encAvg = 0;
	error2 = target2 - encAvg;	//error is the difference between the goal and current distance

	tolerance2 = 0.5;	//how accurate do I want the robot to be was at .25
  kp2 = 1;
	totalError2 = 0;
	ki2 = 0;

	float prevError2 = 0;
	float kd2 = 0;
	time1[T3] = 0;

	while(abs(error2) > tolerance2 && (time1[T3] < 1000))
		{
			encAvg = ((degToInt(SensorValue[REnc]) + degToInt(SensorValue[LEnc]))/2);
			error2 = target2 - encAvg;
		  float dSpeed = ((error2 * kp2) + (totalError2 * ki2) + ((error2 - prevError2) * kd2)) ;//constantly updates as I get closer to target

		  if (abs(dSpeed) < minGo)
			{
			   Right(minGo);
			   Left(minGo);
			}
		  else
		  {
		  		Right(dSpeed);
			    Left(dSpeed);
		  }
			if(abs(error2) < tolerance2*50)
			{
					//kD = 20;
				//	ki = 1;
			}
			if(abs(error2) > tolerance2)
			{
		 		time1[T3] = 0;
			}
				//motor power limits itself to 127 if too large.
				//check to make sure the robot is not stalling before it reaches the target point
					//Note: stalling is either from Kp being too low and doesn't have enough power to push last bit of distance
					//Note: You can eliminate stalling with a minimum speed limit i.e: if(error*kp < MIN){ motor[port[1]] = MIN};

				//*****STEPS TO CALIBRATE Kp*****
				//1. keep increasing Kp until the robot starts to oscillate about the target point physically
				//2. once Kp oscillates, decrease Kp a little so it is stable
		  totalError2 += error2;
		  prevError2 = error2;
		}
	Halt();
	  //}

		//Things to know about P Controllers
		//
}
