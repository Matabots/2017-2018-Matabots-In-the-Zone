/*
Drive Functions (some code taken from Jeff (Robot 1)/Teleoperated Control.h"
Version 2 (added PID controlled lift)
*/
//drive stalls when lift hits an obstacle

int lastPost = 0;
int n =  1;
float minS;
float target;
float enc = 0;
float error;	//error is the difference between the goal and current distance
float tolerance;	//how accurate do I want the robot to be
float Kp;		//Kp is a multiplier to calibrate the power
float totalError;
float ki;
float currentDeg;
bool cone = false;
bool same;
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
};

Controller controller;

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
}
int currentStack = 0;
enum Mode
{
	 TANK = 0,
	 ARCADE =1
};

void MoveArm(float input)
{
	minS = 20;
	target = input;
	error = target - enc;	//error is the difference between the goal and current distance

	tolerance = 3;	//how accurate do I want the robot to be was at .25
  if (cone) {
    Kp = 1.8;
    minS = 30;
  } else  {
	  Kp = 1.3;		//Kp is a multiplier to calibrate the power //1.3 works
  }
  if (input == 0) {
  	minS = 20;
  	tolerance = 5;
  	Kp = 1.7;
  }
	totalError= 0;
	ki = 0;

	float prevError = 0;
	float kD = 200;
	time1[T1] = 0;

	while(same)
		{
			enc = SensorValue[stackEnc];
			error = target - enc;
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
	    if (currentDeg != input) {
	    	same = false;
	    }
		}
	  //}

		//Things to know about P Controllers
		//
		lastPost = target;
		same = true;

}

void MoveClaw()
{
	if(vexRT[controller.clawOpen] == 1 && (SensorValue[Potent] > potentVal - 200)) //&& abs(SensorValue[CMEnc]) < 90)
	{ //open
		motor[CMot] = 127;
  }
  else if(vexRT[controller.clawClose] == 1 && (SensorValue[Potent] < (potentVal + 1000))) //&& abs(SensorValue[CMEnc]) > 0)
  { //close
    motor[CMot] = -127;
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
		  motor[CMot] = 127;
	  }
    motor[CMot] = 20;
    wait10Msec(100);
    cone = false;
  	break;

  case 1:

    cone = true;
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
	if(vexRT[controller.stack])
	{
	  switch ( currentStack )
	 	{
		case 0:
		  oldDeg = currentDeg;

		  AutoClaw(1);

	    currentDeg = 85;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			currentDeg = oldDeg; // parameter will be "lastPos"

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
		  oldDeg = currentDeg;

		  AutoClaw(1);

	    currentDeg = 70;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			currentDeg = oldDeg;
			break;

		case 2:
		  oldDeg = currentDeg;

		  AutoClaw(1);

	    currentDeg = 60;
			wait10Msec(100);

	    AutoClaw(0);
	    wait10Msec(100);

			currentDeg = oldDeg;
			break;
	  }
	  currentStack++;
  }
}

void MoveChassis()
{

	if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	{
		motor[RMots1] = n*vexRT[controller.rightMotors];
		motor[RMots2] = n*vexRT[controller.rightMotors];
		motor[RMots3] = n*vexRT[controller.rightMotors];
	}
	else
	{
		motor[RMots1] = 0;
		motor[RMots2] = 0;
		motor[RMots3] = 0;
	}
	if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	{
		motor[LMots1] = n*vexRT[controller.leftMotors];
		motor[LMots2] = n*vexRT[controller.leftMotors];
		motor[LMots3] = n*vexRT[controller.leftMotors];
	}
	else
	{
		motor[LMots1] = 0;
		motor[LMots2] = 0;
		motor[LMots3] = 0;
	}
}
void StackerSetter()
{
	if(vexRT[controller.GroLift])
	{
		currentDeg = -138;
	}
	if(vexRT[controller.autoLLift])
	{
		currentDeg = -80;
	}
	if(vexRT[controller.resStackNeut])
	{
		currentDeg = 0;
		currentStack = 0;
  }
  if(vexRT[controller.stackUp])
	{
		currentStack = currentStack + 1;
	}

}
void liftBase()
{
		if (vexRT[controller.goalLiftU] == 1 && (SensorValue[LimL1] == 0 && SensorValue[LimR1] == 0))
		{
			motor[MobMots1] = -127;
			motor[MobMots2] = -127;
		}
		else if (vexRT[controller.goalLiftD] == 1)
		{
			motor[MobMots1] = 127;
			motor[MobMots2] = 127;
		}
		else
		{
			motor[MobMots1] = 0;
			motor[MobMots2] = 0;
		}
}
void SetupSens()
{
	currentDeg = 0; //PID arm setup
	//SensorValue[LEnc] = 0; //may affect lift , unsure
	SensorValue[REnc] = 0;
	SensorValue[Gyro] = 0;
  //SensorValue[stackEnc] = 0; //may affect lift enc, unsure
  potentVal = SensorValue[Potent];
}

void runPID()
{
	MoveArm(currentDeg);
}
void runController(const Mode mode = TANK)
{
	MoveChassis();
	AutoLift();
	MoveClaw();
	liftBase();
	StackerSetter();

}
