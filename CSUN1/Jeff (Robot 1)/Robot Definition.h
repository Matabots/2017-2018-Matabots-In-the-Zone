/*the purpose of this file is to create and manipulate the basic functionality
and aspects of a robot*/

/*define the chassis of the robot*/
struct Chassis
{
	float wheelDiameter;	//inches
	Vector2 COR;	//center of rotation. x = 0, y = 0 at middle. + faces forward and right
};

/*define the double 4 bar with lever arm*/
struct Lift
{
	//define combination of bars
	float armBotLength;
	float armTopLength;
	float theta;
	float c1;	//the vertical distance of the side towers in inches
	float c2;	//the vertical distance between the two 4-bars in inches
	Vector2 endPoint;
};

struct Claw
{
	float armLength;
	float alpha;	//the angle between the claw arm and the vertical y-axis
	float c3;	//the vertical distance between the end of the 4-bars and the claw
	Vector2 endPoint;
}


/*define the robot as a sum of other assemblies*/
struct Robot
{
	Claw claw;
	Chassis chassis;
	Lift lift;
};

Robot robot;	//create the global robot that will be controlled by the program

/*once started, this task will constantly update the robot values based on current sensor input*/
task update()
{
	robot.lift.theta = Avg(SensorValue[leftLiftEnc],SensorValue[rightLiftEnc]);
	robot.claw.alpha = SensorValue[ClawLiftAngle];
	robot.lift.endPoint.y =(sin(robot.lift.theta)*(robot.lift.armBotLength+robot.lift.armTopLength))+ robot.lift.c1 + robot.lift.c2;
	robot.claw.endPoint.y = robot.claw.c3+robot.claw.armLength*cos(robot.claw.alpha);
}

/* Initializes the sensors, dimensions, and qualities of the robot.
edit this function to redefine the robot properties*/
void initializeRobot()
{
	robot.chassis.wheelDiameter = 4;
	robot.chassis.COR.x = 0;
	robot.chassis.COR.y = 0;
	robot.lift.armBotLength = 0;
	robot.lift.armTopLength = 0;
	SensorValue[leftLiftEnc] = 0;
	SensorValue[rightLiftEnc] =0;
	SensorValue[ClawLiftAngle]=0;
	robot.lift.theta = Avg(SensorValue[leftLiftEnc],SensorValue[rightLiftEnc]);
	robot.claw.alpha = SensorValue[ClawLiftAngle];
	robot.lift.endPoint.y =(sin(robot.lift.theta)*(robot.lift.armBotLength+robot.lift.armTopLength))+ robot.lift.c1 + robot.lift.c2;
	robot.claw.endPoint.y = robot.claw.c3+robot.claw.armLength*cos(robot.claw.alpha);
	startTask(update);
}


/*Move the claw to a target height*/
void moveClawEndPointTo(int targetHeight)
{
	float kp = 1;
	float ki = 1;
	float error = targetHeight - robot.claw.endPoint.y;
	float totalError = 0;
	int output = 0;
	while(abs(error)> 0.1)
	{
		error = targetHeight - robot.claw.endPoint.y;
		totalError += error;
		output = error*kp + totalError*ki;
		motor[CLift] = output;
	}
	motor[CLift] = 0;
}

void moveLiftEndPointTo(int targetHeight)
{
	float kp = 1;
	float ki = 1;
	float error = targetHeight - robot.lift.endPoint.y;
	float totalError = 0;
	int output = 0;
	int shift =0;
	while(abs(error)> 0.1)
	{
		error = targetHeight - robot.claw.endPoint.y;
		totalError += error;
		output = error*kp + totalError*ki;
		if(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]>0)
		{
			motor[LLift] = output-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
			motor[RLift] = output+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
		}
		else
		{
			motor[LLift] = output+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
			motor[RLift] = output-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
		}
	}
	motor[LLift] = 0;
	motor[RLift] = 0;
}

int stackHeight(int towerHeight)
{
	//
}

void moveTime(int powerLeft, int powerRight, int time)
{
	motor[LRevs] = powerLeft;
	motor[LFors] = powerLeft;
	motor[RRevs] = powerRight;
	motor[RFors] = powerRight;
	wait1Msec(time);
}

void moveDeg(int powerLeft, int powerRight, int deg)
{
  SensorValue[leftEnc] =0;
  SensorValue[rightEnc] = 0;
	while (abs((SensorValue[leftEnc])) < deg && abs((SensorValue[rightEnc])) < deg)
	{
		moveTime(powerLeft,powerRight,0);
  }
  moveTime(powerLeft,powerRight,100);
}

void moveInch(int powerLeft, int powerRight, int inch)
{
  SensorValue[leftEnc] =0;
  SensorValue[rightEnc] = 0;
	while (abs(degToInt(SensorValue[leftEnc])) < inch && abs(degToInt(SensorValue[rightEnc])) < inch)
	{
		moveTime(powerLeft,powerRight,0);
  }
  moveTime(powerLeft,powerRight,100);
}

void GoalLift()
{
	if (vexRT[controller.goalLift] == 1 && (SensorValue[pneuBase] == 0))
	{
		SensorValue[pneuBase] = 1;
		wait10Msec(20);
	}
	if (vexRT[controller.goalLift] == 1 && (SensorValue[pneuBase] == 1))
	{
		SensorValue[pneuBase] = 0;
		wait10Msec(20);
	}
}

void liftBase()
{
	if (SensorValue[pneuBase] == 0)
	{
		SensorValue[pneuBase] = 1;
		wait10Msec(20);
	}
  else if (SensorValue[pneuBase] == 1)
  {
	  SensorValue[pneuBase] = 0;
		wait10Msec(20);
  }
}
