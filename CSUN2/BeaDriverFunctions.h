/*
Drive Functions
*/

#define DEADZONE 15


void rightMotors(int speed)
{
	motor[REdgeMots] = -speed;
	motor[RInsideMots] = speed;
}
void leftMotors(int speed)
{
	motor[LEdgeMots] = speed;
	motor[LInsideMots] = speed;
}
void moveLift(int speed){
	motor[liftMotor1] = speed;
	motor[liftMotor2] = -speed;
}
void haltRight()
{
	motor[REdgeMots] = 0;
	motor[RInsideMots] = 0;
}
void haltLeft()
{
	motor[LEdgeMots] = 0;
	motor[LInsideMots] = 0;
}
void haltLift(){
	motor[liftMotor1] = 0;
	motor[liftMotor2] = 0;
}
void moveconeLift(int speed){
	motor[ConeLift] = speed;
}
void haltconeLift(){
	motor[ConeLift] = 0;
}

void moveClaw(int speed){
	motor[claw] = speed;
}

void haltClaw(){
	motor[claw] = 0;
}

void resetSensor(){
	SensorValue[TopEncoder] = 0;

}

void driveControl()
{
	if (abs(vexRT[Ch2]) > DEADZONE){
		rightMotors(vexRT[Ch2]);
		}else{
		haltRight();
	}
	if (abs(vexRT[Ch3]) > DEADZONE){
		leftMotors(vexRT[Ch3]);
		}else{
		haltLeft();
	}
	if(vexRT[Btn6U]){
		moveLift(127);
		}else if(vexRT[Btn6D]){
		moveLift(-127);
		}else{
		haltLift();
	}
	if(vexRT[Btn5U]){
		moveconeLift(127);
		}else if(vexRT[Btn5D]){
		moveconeLift(-127);
		}else{
		haltconeLift();
	}

	if(vexRT[Btn7U]){
		moveClaw(127);
		}else if(vexRT[Btn7D]){
		moveClaw(-127);
		}else{
		haltClaw();
	}

}
