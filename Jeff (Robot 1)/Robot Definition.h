struct Vector
{
	float x;
	float y;
	float z;
};

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
	float theta;
	float alpha;
	float clawLength;
	float height;
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
}

float ClawEndpoint()
{
	//clawEndpoint = c1+c2+c3+(sin(theta)*(x1+x2))+(c3*sing(alpha))

}

int stackHeight()
{

}
