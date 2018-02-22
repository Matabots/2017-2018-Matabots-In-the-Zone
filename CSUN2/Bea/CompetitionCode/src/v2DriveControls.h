/*
Drive Functions (some code taken from Jeff (Robot 1)/Teleoperated Control.h"
Version 2 (added PID controlled lift)
*/
//since the auton code uses the same value names, the letter "D" was added to avoid similarity since values are different.
float Kp;		//Kp is a multiplier to calibrate the power

#define DEADZONE 15
struct Controller
{
	TVexJoysticks smallLiftGround;
	TVexJoysticks stackUp;
	TVexJoysticks mobileGoalLiftGround;
	TVexJoysticks mobileGoalLiftHigh;
	TVexJoysticks rightMotors;
	TVexJoysticks	leftMotors;
	TVexJoysticks	smallLiftDown;
	TVexJoysticks smallLiftUp;
	TVexJoysticks mobileGoalLiftUp;
	TVexJoysticks mobileGoalLiftDown;
	TVexJoysticks resStackNeut;
	TVexJoysticks coneBool;
	TVexJoysticks decliner;
	TVexJoysticks smallLiftHigh;
};

Controller controller;

void setupController()
{
	controller.rightMotors = Ch2;	//move the right side of the robot
	controller.leftMotors = Ch3;	//move the left side of the robot
	controller.smallLiftDown = Btn5D;	//open claw
	controller.smallLiftUp = Btn5U;	//close claw
	controller.smallLiftGround = Btn7D; //activate stacker
	controller.smallLiftHigh = Btn7L; //closes the claw
	controller.mobileGoalLiftUp = Btn6U; //lift  the goal
	controller.mobileGoalLiftDown = Btn6D; //lower the goal
	controller.mobileGoalLiftGround = Btn8R; //ground collector position
	controller.mobileGoalLiftHigh = Btn8D; //autoload position
	controller.resStackNeut = Btn7U; //reset smallLiftGround # and set lift to neut
}
enum Mode
{
	 TANK = 0,
	 ARCADE =1
};

void MoveArm(float input)
{
	minS = 20;
	target = input;
	error = target - pitch;	//error is the difference between the goal and current distance
	float prevError = 0;
	float kD = 200;

	tolerance = 3;	//how accurate do I want  robot to be was at .25
  if (cone) {
    Kp = 1.7; //was 1.8
    minS = 30;
    tolerance = 8;
  } else  {
	  Kp = 1.3;		//Kp is a multiplier to calibrate the power //1.3 works
  }
  if (input == 0) {
  	minS = 20;
  	tolerance = 5;
  	Kp = 1.7;
  }
  if (targetDeg == firstCone) //was currentStack, but that caused issues
  {
    Kp = 2.0;
    kD = 400;
    tolerance = 8;
  }
	totalError = 0;
	ki = 0;
	time1[T1] = 0;

	while(same)
		{
			enc = SensorValue[TopEncoder];
			pitch = enc + offSet;
			error = target - pitch;
			float motSpeed;
			if (target == 0)
		  {
		    motSpeed = -((error * Kp) + (totalError * ki) + ((error - prevError) * 0/*kD*/)) ;//constantly updates as I get closer to target
		  } else {
			  motSpeed = -((error * Kp) + (totalError * ki) + ((error - prevError) * kD)) ;//constantly updates as I get closer to target
		  }
			if (abs(motSpeed) < minS)
			{
			  if (motSpeed < 0) {
			    motor[ConeLift] = -minS;
			  } else {
			    motor[ConeLift] = minS;
			  }
			}
		  else
		  {

		  		motor[ConeLift] = motSpeed;

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
	    if (targetDeg != input) {
	    	same = false;
	    }
		}
		lastPost = target;
		same = true;

}

void MoveClaw()
{
	//ADJUST FOR INTEGRATED ENCODER
	// if(vexRT[controller.smallLiftDown] == 1 && (SensorValue[Potent] > potentVal - 200)) //&& abs(SensorValue[CMEnc]) < 90)
	// { //open
	// 	motor[CMot] = -127;
  // }
  // else if(vexRT[controller.smallLiftUp] == 1 && (SensorValue[Potent] < (potentVal + 1000))) //&& abs(SensorValue[CMEnc]) > 0)
  // { //close
  //   motor[CMot] = 127;
  // }
  // else
  // {
  // 	motor[CMot] = 0;
  // }
}

void AutoClawD(int IO) //0 is open, 1 is closed
{
	//ADJUST FOR INTEGRATED ENCODER
	// //open claw
	// switch(IO)
	// {
  // case 0:
  //   time1[T1] = 0;
  //   while((SensorValue[Potent] > potentVal - 300) && (time1[T1] < 1500))
	//   {
	// 	  motor[CMot] = -127;
	//   }
  //   motor[CMot] = -20;
  //   wait10Msec(100);
  //   cone = false;
  //   same = false;
  // 	break;
	//
  // case 1:
	//
  //   cone = true;
  //   motor[CMot] = 25;
  // 	break;
  // }
}


void AutoLiftD()
{
	float oldDeg;
	if(vexRT[controller.smallLiftGround])
	{
	  switch ( currentStack )
	 	{
		case 0:
		  oldDeg = targetDeg;

		  AutoClawD(1);

	    targetDeg = firstCone;
			wait10Msec(170);

	    AutoClawD(0);
	    wait10Msec(50);

		  targetDeg = oldDeg;
			same = false;// goes back to old position
			break;

		case 1:
		  oldDeg = targetDeg;

		  AutoClawD(1);

	    targetDeg = secondCone;
			wait10Msec(150);

	    AutoClawD(0);
	    wait10Msec(50);

			targetDeg = oldDeg;
			break;

		case 2:
		  oldDeg = targetDeg;

		  AutoClawD(1);

	    targetDeg = thirdCone;
			wait10Msec(130);

	    AutoClawD(0);
	    wait10Msec(50);

			targetDeg = oldDeg;
			break;
	  }
	  currentStack++;
  }
}

void MoveChassis()
{
  if (polarity)
  {
	  if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	  {
		  motor[LEdgeMots] = -n*vexRT[controller.rightMotors];
		  motor[LInsideMots] = -n*vexRT[controller.rightMotors];
	  }
	  else
	  {
		  motor[LEdgeMots] = 0;
		  motor[LInsideMots] = 0;
	  }
	  if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	  {
		  motor[REdgeMots] = -n*vexRT[controller.leftMotors];
		  motor[RInsideMots] = -n*vexRT[controller.leftMotors];
	  }
	  else
	  {
		  motor[REdgeMots] = 0;
		  motor[RInsideMots] = 0;
	  }
  }
  else
  {
  	if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	  {
		  motor[REdgeMots] = n*vexRT[controller.rightMotors];
		  motor[RInsideMots] = n*vexRT[controller.rightMotors];
	  }
	  else
	  {
		  motor[REdgeMots] = 0;
		  motor[RInsideMots] = 0;
	  }
	  if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	  {
		  motor[LEdgeMots] = n*vexRT[controller.leftMotors];
		  motor[LInsideMots] = n*vexRT[controller.leftMotors];
	  }
	  else
	  {
		  motor[LEdgeMots] = 0;
		  motor[LInsideMots] = 0;
	  }
  }
}
void StackerSetter()
{
	if(vexRT[controller.mobileGoalLiftGround])
	{
		targetDeg = -136;
	}
	if(vexRT[controller.mobileGoalLiftHigh])
	{
		targetDeg = -80;
	}
	if(vexRT[controller.resStackNeut])
	{
		targetDeg = 0;
		currentStack = 0;
  }
  /*if(vexRT[controller.stackUp])
	{
		currentStack = currentStack + 1;
	}*/ //broken code

}
void liftBase()
{
	//ADJUST FOR POTENTIOMETER
		// if (vexRT[controller.mobileGoalLiftUp] == 1 && (SensorValue[LimL1] == 0 && SensorValue[LimR1] == 0))
		// {
		// 	motor[MobMots1] = -127;
		// 	motor[MobMots2] = -127;
		// }
		// else if (vexRT[controller.mobileGoalLiftDown] == 1)
		// {
		// 	motor[MobMots1] = 127;
		// 	motor[MobMots2] = 127;
		// }
		// else
		// {
		// 	motor[MobMots1] = 0;
		// 	motor[MobMots2] = 0;
		// }
}
void runPID()
{
	MoveArm(targetDeg);
}
void lift()
{
	AutoLiftD();
}
void driveCheck()
{
  if(vexRT[controller.smallLiftHigh] == 1)
  {
  	polarity = !polarity;
  	wait10Msec(20);
  }
}
void LEDSet()
{
	int i = 8 + currentStack;
	if (currentStack  != 0)
	{
		SensorValue[(tSensors) i ] = 1;
  }
  else
  {
		SensorValue[(tSensors) i + 1 ] = 0;
		SensorValue[(tSensors) i + 2 ] = 0;
		SensorValue[(tSensors) i + 3 ] = 0;
	}
	if (polarity == true)
	{
		SensorValue[(tSensors) 8 ] = 1;
	}
	else
  {
  	SensorValue[(tSensors) 8 ] = 0;
  }
}
void setVariables()
{
	lastPost = 0;
	n =  1;
	firstCone = 83;
	secondCone = 75;
	thirdCone = 58;
	cone = false;
	potentVal = 0;
	currentStack = 0;
	offSet = 0;
}

void runController(const Mode mode = TANK)
{
	driveCheck();
	MoveChassis();
	MoveClaw();
	liftBase();
	StackerSetter();
	LEDSet();
}
