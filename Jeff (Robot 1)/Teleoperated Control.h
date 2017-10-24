/*
Teleoperated Control
*/
#define DEADZONE 15

struct Controller
{
	TVexJoysticks liftUp;
	TVexJoysticks liftDown;
	TVexJoysticks	clawUp;
	TVexJoysticks clawDown;
	TVexJoysticks rightMotors;
	TVexJoysticks	leftMotors;
	TVexJoysticks	clawOpen;
	TVexJoysticks clawClose;
	TVexJoysticks goalLift;
};

Controller controller;

void setupController()
{
	controller.liftUp = Btn7U; //edited
	controller.liftDown = Btn7D;
	controller.clawUp = Btn5U; //mini 4 bar
	controller.clawDown = Btn5D;
	controller.rightMotors = Ch2;
	controller.leftMotors = Ch3;
	controller.clawOpen = Btn6U;
	controller.clawClose = Btn6D;
	controller.goalLift = Btn8R;
}


enum Mode
{
	 TANK = 0,
	 ARCADE =1
};

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

void MoveLift()
{
	//moves the entire arm up/down
	 	if(vexRT[controller.liftUp])
	 	{
    	motor[RLift] = 127;
  		motor[LLift] = 127;
    }
	  else if(vexRT[controller.liftDown])
	 	{
	   	motor[RLift] = -127;
   		motor[LLift] = -127;
    }
    else
    {
		  motor[RLift] = 0;
		  motor[LLift] = 0;
		}
	//moves the claw clockwise/counter clockwise
		if(vexRT[controller.clawUp])
	 	{
    	motor[CLift] = 127;
    }
	  else if(vexRT[controller.clawDown])
	 	{
	   	motor[CLift] = -127;
    }
    else
    {
		  motor[CLift] = 0;
		}
}

void MoveClaw()
{
	if(vexRT(controller.clawOpen))
	{
		motor[CMot] = 127;
  }
  else if(vexRT(controller.clawClose))
  {
    motor[CMot] = -127;
  }
  else
  {
  	motor[CMot] = 0;
  }
}

void MoveChassis()
{
	int deadZone = 15;
	if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	{
		motor[RRevs] = -vexRT[controller.rightMotors];
		motor[RFors] = vexRT[controller.rightMotors]; //wires have reverse polarity
	}
	else
	{
		motor[RRevs] =0;
		motor[RFors] = 0; //wires have reverse polarity
	}
	if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	{
		motor[LRevs] = -vexRT[controller.leftMotors];
		motor[LFors] = vexRT[controller.leftMotors]; //wires have reverse polarity
	}
	else
	{
		motor[LRevs] = 0;
		motor[LFors] = 0; //wires have reverse polarity
	}
}

void runController(const Mode mode = TANK)
{
	switch(mode)
	{
		case TANK:
			MoveChassis();
			MoveLift();
			MoveClaw();
		break;

		case ARCADE:
			//currently no implementation
		break;
	}
}
