////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////This will define a struct to control the ////////////////////////////////////////////////////////////////////////////////////////
//////////////////////sensors, motors, and controller for the robot/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct AnalogSensor{
  tSensors liftPot; //this will have control of the goal lift
  tSensors gyro;
};

AnalogSensor aSensors;

struct DigitalSensor{
  tSensors rightEncoder; //right wheel encoder
  tSensors leftEncoder; //left wheel encoder
  tSensors coneLiftEnc;	//the cone lift encoder
};
DigitalSensor dSensors;

struct RobotMotor{
  tMotor frontLeft;
  tMotor rearLeft;
  tMotor frontRight;
  tMotor rearRight;
  tMotor lift1;
  tMotor lift2;
  tMotor smallLift;
  tMotor ef;
};
RobotMotor rMotors;

struct Communications{
 	//TI2CStatus i2c;


};

Communications comms;

struct Robot{
	//reference child struct data types with pointers
	//Ex: robot.rMotors->frontLeft
  struct AnalogSensor *aSensors;
  struct DigitalSensor *dSensors;
  struct RobotMotor *rMotors;
  struct Communications *comms;
};

Robot robot;

void setupAnalogSensor(){
  (aSensors).liftPot = LiftPotentiometer; //this will have control of the goal lift
  (aSensors).gyro = Gyro;
}

void setupDigitalSensor(){
  (dSensors).rightEncoder = REnc; //right wheel encoder
  (dSensors).leftEncoder = LEnc; //left wheel encoder
  (dSensors).coneLiftEnc = ConeLiftEncoder;
}

void setupMotors(){
	 (rMotors).frontRight = REdgeMots;
   (rMotors).rearRight = RInsideMots;
   (rMotors).frontLeft = LEdgeMots;
   (rMotors).rearLeft = LInsideMots;
   (rMotors).lift1 = LiftMotor1;
   (rMotors).lift2 = LiftMotor2;
   (rMotors).smallLift = ConeLift;
   (rMotors).ef = Claw;
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

void goalLiftMovement(int moveUp){
	if(moveUp == 1){
		motor[robot.rMotors->lift1] = 127;
		motor[robot.rMotors->lift2] = -127;
	}else if(moveUp == -1){
		motor[robot.rMotors->lift1] = -127;
		motor[robot.rMotors->lift2] = 127;
	}else{
		motor[robot.rMotors->lift1] = 0;
		motor[robot.rMotors->lift2] = 0;
	}
}

void coneLiftMovement(int moveUp){
	if(moveUp == 1){
		motor[robot.rMotors->smallLift] = -127;
	}else if(moveUp == -1){
		motor[robot.rMotors->smallLift] = 127;
	}else{
		motor[robot.rMotors->smallLift] = 0;
	}
}

void controlClaw(int grasp){
	if(grasp == 1){
		motor[robot.rMotors->ef] = -127;
		wait1Msec(10);
	}else if(grasp == -1){
		motor[robot.rMotors->ef] = 127;
		wait1Msec(10);
	}else{
		motor[robot.rMotors->ef] = 0;
	}
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
	TVexJoysticks clawOpen;
	TVexJoysticks clawClose;
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
	controller.clawOpen = Btn8U;
	controller.clawClose = Btn8L;
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

void goalLiftControls(){
	//-1 move goal down //0 kills movement //and 1 sends it up
	if(vexRT[controller.mobileGoalLiftDown] == 1){
		goalLiftMovement(-1);
	}else if(vexRT[controller.mobileGoalLiftUp] == 1){
		goalLiftMovement(1);
	}else{
		goalLiftMovement(0);
	}
}

void coneLiftControls(){
		//-1 move cone down //0 kills movement //and 1 sends it up
	if(vexRT[controller.smallLiftDown] == 1){
		coneLiftMovement(-1);
	}else if(vexRT[controller.smallLiftUp] == 1){
		coneLiftMovement(1);
	}else{
		coneLiftMovement(0);
	}
}

void clawControls(){
	if(vexRT[controller.clawClose] == 1){
		controlClaw(-1);
	}else if(vexRT[controller.clawOpen] == 1){
		controlClaw(1);
	}else{
		controlClaw(0);
	}
}

void controllerInputs(){
  joystickControls();
	goalLiftControls();
	coneLiftControls();
	clawControls();
}

void readSensors(){

}
