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
bool cone = false;
#define DEADZONE 15
int potentVal = 0;

struct Controller
{
	TVexJoysticks stack;
	TVexJoysticks rightMotors;
	TVexJoysticks	leftMotors;
	TVexJoysticks	clawOpen;
	TVexJoysticks clawClose;
	TVexJoysticks goalLift;
	TVexJoysticks resetStack;
};

Controller controller;

void setupController()
{
	controller.stack = Btn7U; //activate lift
	controller.rightMotors = Ch2;	//move the right side of the robot
	controller.leftMotors = Ch3;	//move the left side of the robot
	controller.clawOpen = Btn6U;	//open claw
	controller.clawClose = Btn6D;	//close claw
	controller.goalLift = Btn8R;	//lift/lower the goal
	controller.resetStack = Btn7L; //reset stack #
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

	while(abs(error) > tolerance || time1[T1] < 2000)
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
		}
	  //}

		//Things to know about P Controllers
		//
		lastPost = target;

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
    while((SensorValue[Potent] > potentVal - 200) && (time1[T1] < 3000))
	  {
		  motor[CMot] = 127;
	  }
    motor[CMot] = 0;
    wait10Msec(100);
    cone = false;
  	break;

  case 1:
    time1[T1] = 0;
    while((SensorValue[Potent] < potentVal + 2000) && (time1[T1] < 3000))//&& abs(SensorValue[CMEnc]) > 0)
    { //close
      motor[CMot] = -127;
    }
    motor[CMot] = 0;
    wait10Msec(100);
    cone = true;

  	break;
  }
}


void AutoLift()
{
	//moves stacker up to 4 cones
	if(vexRT[controller.stack])
	{
	  switch ( currentStack )
	 	{
		case 0:
		  MoveArm(-138);
		  wait10Msec(300);

		  AutoClaw(1);

	    MoveArm(100);
			wait10Msec(100);

	    AutoClaw(0);

			MoveArm(0); // parameter will be "lastPos"

			break;

		case 1:
		  MoveArm(-138);
		  wait10Msec(300);

		  AutoClaw(1);

	    MoveArm(80);


	    AutoClaw(0);

			MoveArm(0); // parameter will be "lastPos"
			break;

		case 2:
		  MoveArm(-138);
		  wait10Msec(300);

		  AutoClaw(1);

	    MoveArm(80);


	    AutoClaw(0);

			MoveArm(0); // parameter will be "lastPos"
			break;

		case 3:
		  MoveArm(-138);
		  wait10Msec(300);

		  AutoClaw(1);

	    MoveArm(75);


	    AutoClaw(0);

			MoveArm(0); // parameter will be "lastPos"
			break;

		case 4:
		  MoveArm(-138);
		  wait10Msec(300);

		  AutoClaw(1);

	    MoveArm(60);


	    AutoClaw(0);

			MoveArm(0); // parameter will be "lastPos"
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
void resetStackerNum()
{
	if(vexRT[controller.resetStack])
	{
		currentStack = 0;
  }
}
void liftBase()
{
	//lift base
}
void SetupSens()
{
	//SensorValue[LEnc] = 0;
	//SensorValue[REnc] = 0;
	//SensorValue[Gyro] = 0;
  //SensorValue[stackEnc] = 0;
  potentVal = SensorValue[Potent];
}

void armControl(int deg)
{
	enc = SensorValue[stackEnc];
	minS = 20;
	target = deg;
	error = target - enc;	//error is the difference between the goal and current distance

	tolerance = 3;	//how accurate do I want the robot to be was at .25
  if (cone) {
    Kp = 1.8;
    minS = 30;
  } else  {
	  Kp = 1.3;		//Kp is a multiplier to calibrate the power //1.3 works
  }
  if (target == 0) {
  	minS = 20;
  	tolerance = 5;
  	Kp = 1.7;
  }
	totalError= 0;
	ki = 0;

	float prevError = 0;
	float kD = 200;
	while(abs(error) > tolerance)
		{
			target = deg;
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
		}
}

void runPID()
{
	armControl(lastPost);
}
void runController(const Mode mode = TANK)
{
	//MoveChassis();
	AutoLift();
	SetupSens();
	//MoveLift();
	//MoveClaw();
	//liftBase();
	resetStackerNum();
}
