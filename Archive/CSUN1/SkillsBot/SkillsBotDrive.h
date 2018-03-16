//Drive
int n = 1;
#define DEADZONE 15
bool polarity = false;
struct Controller
{
	TVexJoysticks rightMotors;
	TVexJoysticks leftMotors;
	TVexJoysticks goalLiftU;
	TVexJoysticks goalLiftD;
	TVexJoysticks revDrive;
};

Controller controller;

void setupController()
{
	controller.rightMotors = Ch2;
	controller.leftMotors = Ch3;
	controller.goalLiftU = Btn6U;
	controller.goalLiftD = Btn6D;
	controller.revDrive = Btn8U;
}

void MoveChassis()
{
  if (polarity)
  {
	  if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	  {
		  motor[LMots1] = -n*vexRT[controller.rightMotors];
		  motor[LMots2] = -n*vexRT[controller.rightMotors];
		  motor[LMots3] = -n*vexRT[controller.rightMotors];
		  motor[LMots4] = -n*vexRT[controller.rightMotors];
	  }
	  else
	  {
		  motor[LMots1] = 0;
		  motor[LMots2] = 0;
		  motor[LMots3] = 0;
		  motor[LMots4] = 0;
	  }
	  if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	  {
		  motor[RMots1] = -n*vexRT[controller.leftMotors];
		  motor[RMots2] = -n*vexRT[controller.leftMotors];
		  motor[RMots3] = -n*vexRT[controller.leftMotors];
		  motor[RMots4] = -n*vexRT[controller.rightMotors];
	  }
	  else
	  {
		  motor[RMots1] = 0;
		  motor[RMots2] = 0;
		  motor[RMots3] = 0;
		  motor[RMots4] = 0;
	  }
  }
  else
  {
  	if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	  {
		  motor[RMots1] = n*vexRT[controller.rightMotors];
		  motor[RMots2] = n*vexRT[controller.rightMotors];
		  motor[RMots3] = n*vexRT[controller.rightMotors];
		  motor[RMots4] = n*vexRT[controller.rightMotors];
	  }
	  else
	  {
		  motor[RMots1] = 0;
		  motor[RMots2] = 0;
		  motor[RMots3] = 0;
		  motor[RMots4] = 0;
	  }
	  if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	  {
		  motor[LMots1] = n*vexRT[controller.leftMotors];
		  motor[LMots2] = n*vexRT[controller.leftMotors];
		  motor[LMots3] = n*vexRT[controller.leftMotors];
		  motor[LMots4] = n*vexRT[controller.leftMotors];
	  }
	  else
	  {
		  motor[LMots1] = 0;
		  motor[LMots2] = 0;
		  motor[LMots3] = 0;
		  motor[LMots4] = 0;
	  }
  }
}

void liftBase()
{
	if (vexRT[controller.goalLiftU] == 1)// && (SensorValue[LimL1] == 0 && SensorValue[LimR1] == 0))
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

void driveCheck()
{
  if(vexRT[controller.revDrive] == 1)
  {
  	polarity = !polarity;
  	wait10Msec(20);
  }
}

void runController()
{
	//driveCheck(); //(reverses drive)
	MoveChassis();
	liftBase();
}

void drive()
{
  setupController();
  while(true)
  {
    runController();
  }
}
