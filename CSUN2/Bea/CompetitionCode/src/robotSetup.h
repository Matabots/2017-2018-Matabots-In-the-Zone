////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////This will define a struct to control the ////////////////////////////////////////////////////////////////////////////////////////
//////////////////////sensors, motors, and controller for the robot/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AnalogSensor{
  tSensors liftPotentiometer1; //this will have control of the goal lift
  tSensors liftPotentiometer2;  //this will have control of the cone lift
};

AnalogSensor aSensors;

struct DigitalSensor{
  tSensors rightEncoder1; //right wheel encoder
  tSensors leftEncoder1; //left wheel encoder
};
DigitalSensor dSensors;

struct RobotMotor{
  tMotor frontLeft;
  tMotor rearLeft;
  tMotor frontRight;
  tMotor rearRight;
  tMotor lift1;
  tMotor lift2;
  tMotor smallLift1;
  tMotor ef;
};
RobotMotor rMotors;

struct Communications{
 	int fun;

};

Communications comms;

struct Robot{
  struct AnalogSensor *aSensors;
  struct DigitalSensor *dSensors;
  struct RobotMotor *rMotors;
  struct Communications *comms;
};

Robot robot;

void setupAnalogSensor(){
  (aSensors).liftPotentiometer1 = BottomLift; //this will have control of the goal lift
  (aSensors).liftPotentiometer2 = TopLift;  //this will have control of the cone lift
}

void setupDigitalSensor(){
  (dSensors).rightEncoder1 = REnc; //right wheel encoder
  (dSensors).leftEncoder1 = LEnc; //left wheel encoder
}

void setupMotors(){
	 (rMotors).frontRight = REdgeMots;
   (rMotors).rearRight = RInsideMots;
   (rMotors).frontLeft = LEdgeMots;
   (rMotors).rearLeft = LInsideMots;
   (rMotors).lift1 = liftMotor1;
   (rMotors).lift2 = liftMotor2;
   (rMotors).smallLift1 = ConeLift;
   (rMotors).ef = claw;
}

void setupCommunications(){


}

void robotSetup(){
  setupAnalogSensor();
  setupCommunications();
  setupDigitalSensor();
  setupMotors();
  robot.aSensors = &aSensors;
  robot.dSensors = &dSensors;
  robot.rMotors = &rMotors;
  robot.comms = &comms;
}

void left(int speed){
  motor[robot.rMotors->frontLeft] = speed;
  motor[robot.rMotors->rearLeft] = speed;
}

void right(int speed){
  motor[robot.rMotors->frontRight] = -speed;
  motor[robot.rMotors->rearRight] = speed;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////This will define a struct to control the ////////////////////////////////////////////////////////////////////////////////////////
//////////////////////controller/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Controller
{
	int deadzone;
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
  controller.deadzone = 15; //deadzone
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

void joystickControls(){
  if (abs(vexRT[controller.rightMotors]) > controller.deadzone){
    right(vexRT[controller.rightMotors]);
    }else{
    right(0);
  	}
  if (abs(vexRT[controller.leftMotors]) > controller.deadzone){
    left(vexRT[controller.leftMotors]);
    }else{
    left(0);
  }
}

void controllerInputs(){
  joystickControls();

}
