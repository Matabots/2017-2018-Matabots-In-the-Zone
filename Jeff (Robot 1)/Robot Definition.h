struct Chassis
{
	float wheelDiameter;	//inches
	Vector COR;	//center of rotation. x = 0, y = 0 at middle. + faces forward and right
};

struct Lift
{
	//define combination of bars
	float armBotLength;
	float armTopLength;
	float armClawLength;
	float theta;
	float alpha;
	float c1;//the vertical distance of the side towers in inches
	float c2;//the vertical distance between the two 4-bars in inches
	float c3;//the vertical distance between the end of the 4-bars and the claw
	float clawEndPoint;
};

struct Robot
{
	Chassis chassis;
	Lift lift;
};

Robot robot;

void initializeRobot()
{
	robot.chassis.wheelDiameter = 4;
	robot.chassis.COR.x = 0;
	robot.chassis.COR.y = 0;
	robot.lift.armBotLength = 0;
	robot.lift.armTopLength = 0;
	//robot.lift.theta = Avg(SensorValue[],SenorValue[]);
	robot.lift.alpha = SensorValue[ClawLiftAngle];
	robot.lift.clawEndpoint =(sin(robot.lift.theta)*(robot.lift.armBotLength+robot.lift.armTopLength))+(robot.lift.armClawLength*sin(robot.lift.alpha))+ robot.lift.c1 + robot.lift.c2 + robot.lift.c3;
}


int stackHeight()
{

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
