////////////////////////////////////////////////////////////////
// This defines a struct to handle the sensors, motors, and   //
// controller of the robot. It keeps track of the ports and   //
// accepts input from the controller                          //
////////////////////////////////////////////////////////////////

#include "Variables.h"
struct AnalogSensor{
  tSensors gyroscope;
};

AnalogSensor aSensors;

struct DigitalSensor{
  tSensors rightEncoder; //right wheel encoder
  tSensors leftEncoder; //left wheel encoder
  tSensors coneLiftEnc;	//the cone lift encoder
  tSensors LiftEnc; //the goal lift encoder
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
 	TI2CStatus i2c;

};

Communications comms;

struct Robot{
	//reference child struct data types with pointers
	//Ex: robot.rMotors->frontLeft
  struct AnalogSensor *aSensors;
  struct DigitalSensor *dSensors;
  struct RobotMotor *rMotors;
  struct Communications *comms;
  int smallLiftLimitDown;
  int smallLiftLimitUp;
  int goalLiftLimitDown;
  int goalLiftLimitUp;
};

Robot robot;

void setupAnalogSensor(){
  (aSensors).gyroscope = Gyro;
}

void setupDigitalSensor(){
  (dSensors).rightEncoder = REnc; //right wheel encoder
  (dSensors).leftEncoder = LEnc; //left wheel encoder
  (dSensors).coneLiftEnc = ConeLiftEncoder; //lift above the encoder of the
  (dSensors).LiftEnc = LiftEncoder; //encoder for the goal lift
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
 	robot.smallLiftLimitDown = 600;
  robot.smallLiftLimitUp = 0;
  robot.goalLiftLimitDown = 55;
  robot.goalLiftLimitUp = 0;
}

void left(int speed){
  motor[robot.rMotors->frontLeft] = speed;
  motor[robot.rMotors->rearLeft] = speed;
}

void smallLift(int speed){
  motor[robot.rMotors->smallLift] = speed;
}

void right(int speed){
  motor[robot.rMotors->frontRight] = -speed;
  motor[robot.rMotors->rearRight] = speed;
}

void resetChassisEnc()
{
	SensorValue[robot.dSensors->rightEncoder] = 0;
	SensorValue[robot.dSensors->leftEncoder] = 0;
}

// resets gyroscope values
void resetGyro() //this function can be used to subtract a rate of change for the gyro to account for drift
{
  SensorValue[robot.aSensors->gyroscope] = 0;
  deltaGyro = 0;
  float prevGyro = 0;
	time1[T1] = 0;
  while(time1[T1] < 2000)
  {
	  right(0);
	  left(0);
		prevGyro = gyroVal;
		wait1Msec(10);
		gyroVal = SensorValue[robot.aSensors->gyroscope];
		deltaGyro = (gyroVal - prevGyro);
	}
}

void goalLiftMovement(int moveUp){// -1 moves the arm down
	if(moveUp == 1 && SensorValue[robot.dSensors->LiftEnc] > robot.goalLiftLimitUp){
		motor[robot.rMotors->lift1] = 127;
		motor[robot.rMotors->lift2] = -127;
	}else if(moveUp == -1 && abs(SensorValue[robot.dSensors->LiftEnc]) < robot.goalLiftLimitDown){
		motor[robot.rMotors->lift1] = -127;
		motor[robot.rMotors->lift2] = 127;
		robot.goalLiftLimitUp = 5;
	}else{
		motor[robot.rMotors->lift1] = 0;
		motor[robot.rMotors->lift2] = 0;
	}
}

// sends power to the motor that controls the cone lift depending on the sensor value and
// whether its corresponding button is pressed
void coneLiftMovement(int moveUp){
	if(moveUp == 1 && (SensorValue[robot.dSensors->ConeLiftEnc] > robot.smallLiftLimitUp)){
		motor[robot.rMotors->smallLift] = -127;
	}else if(moveUp == -1 && (SensorValue[robot.dSensors->ConeLiftEnc] < robot.smallLiftLimitDown)){
		motor[robot.rMotors->smallLift] = 127;
		robot.smallLiftLimitUp = 5;
	}else{
		motor[robot.rMotors->smallLift] = 0;
	}
}

// sends power to the motor that controls the end-effector depending on
// whether its corresponding button is pressed
void controlClaw(int grasp){
	int clawDeadzone = 5;
	if(grasp == 1){
			motor[robot.rMotors->ef] = -75;
			wait1Msec(250);
	}else if(grasp == -1){
			motor[robot.rMotors->ef] = 75;
			wait1Msec(250);
	}
		motor[robot.rMotors->ef] = 0;

}

///////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//This defines a struct to handle controller input.              //
//It maps the control buttons to their respective functions.     //
//The modularity of the structure and functions makes it easier  //
//to remap when needed.                                          //
///////////////////////////////////////////////////////////////////

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
	controller.mobileGoalLiftUp = Btn6D; //lift  the goal
	controller.mobileGoalLiftDown = Btn6U; //lower the goal
	controller.mobileGoalLiftGround = Btn8R; //ground collector position
	controller.mobileGoalLiftHigh = Btn8D; //autoload position
	controller.clawOpen = Btn8L;
	controller.clawClose = Btn8D;
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

// intializes sensor values
void intializeSensorValues(){
	SensorValue(robot.dSensors->rightEncoder) = 0;
	SensorValue(robot.dSensors->leftEncoder) = 0;
	SensorValue(robot.dSensors->coneLiftEnc) = 0;
	SensorValue(robot.dSensors->LiftEnc) = 0;
}

// checks sensor values for debugging purposes
void outputSensorData(){
	writeDebugStream("%d\n", SensorValue(robot.dSensors->LiftEnc));
  //writeDebugStream("%d\n", SensorValue(robot.aSensors->gyroscope));
  //writeDebugStream("%d\n", SensorValue(robot.dSensors->rightEncoder));
	//writeDebugStream("%d\n", SensorValue(robot.dSensors->leftEncoder));
	//writeDebugStream("%d\n", SensorValue(robot.dSensors->coneLiftEnc));
}
