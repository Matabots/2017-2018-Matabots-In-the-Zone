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
	controller.liftUp = Btn7U; //move the lift up
	controller.liftDown = Btn7D;	//move the lift down
	controller.clawUp = Btn5U; //move claw up
	controller.clawDown = Btn5D;	//move claw down
	controller.rightMotors = Ch2;	//move the right side of the robot
	controller.leftMotors = Ch3;	//move the left side of the robot
	controller.clawOpen = Btn6U;	//open claw
	controller.clawClose = Btn6D;	//close claw
	controller.goalLift = Btn8R;	//lift/lower the goal
}


enum Mode
{
	 TANK = 0,
	 ARCADE =1
};

void MoveLift()
{
	//moves the entire arm up/down
	 	if(vexRT[controller.liftUp])
	 	{
	 		if(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]>0)
		 	{
	    	motor[RLift] = 127+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
	  		motor[LLift] = 127-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
  		}
  		else
  		{
	    	motor[RLift] = 127-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
	  		motor[LLift] = 127+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
  		}
    }
	  else if(vexRT[controller.liftDown])
	 	{
	   	if(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]>0)
		 	{
	    	motor[RLift] = -127+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
	  		motor[LLift] = -127-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
  		}
  		else
  		{
	    	motor[RLift] = -127-(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
	  		motor[LLift] = -127+(SensorValue[leftLiftEnc]-SensorValue[rightLiftEnc]);
  		}
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
	if(vexRT(controller.clawOpen)) //&& abs(SensorValue[CMEnc]) < 90)
	{
		motor[CMot] = -127;
  }
  else if(vexRT(controller.clawClose)) //&& abs(SensorValue[CMEnc]) > 0)
  {
    motor[CMot] = 127;
  }
  else
  {
  	motor[CMot] = 0;
  }
  displayLCDNumber(1,3,getMotorEncoder(CMot))
}

void MoveChassis()
{
	int deadZone = 15;
	if (abs(vexRT[controller.rightMotors]) > DEADZONE)
	{
		motor[RRevs] = vexRT[controller.rightMotors];
		motor[RFors] = vexRT[controller.rightMotors]; //wires have reverse polarity
	}
	else
	{
		motor[RRevs] =0;
		motor[RFors] = 0; //wires have reverse polarity
	}
	if (abs(vexRT[controller.leftMotors]) > DEADZONE)
	{
		motor[LRevs] = vexRT[controller.leftMotors];
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
			GoalLift();
		break;

		case ARCADE:
			//currently no implementation
		break;
	}
}
