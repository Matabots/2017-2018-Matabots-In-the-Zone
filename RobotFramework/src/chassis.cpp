#include "chassis.h"

chassis::chassis(){
  this->wheelDiameter = 4; //inches
  //this->chassisVelPID = new pid(10,3.48,896.9,0.0);
  this->chassisVelPID = new pid(1.5,0.0,0.0,0.0);
  //this->chassisPosPID = new pid(0.45,0.0,0.0125,0.0);//4.0,0,0
                          //0.45                      //0.85,0,0 for gyro turn
  // this->chassisPosPID = new pid(0.85,0.024,0.016,0.0);
  // this->chassisPosPID->set_deadband(10);
  this->chassisPosPID = new pid(3.5,0.0,0.0,0.0); //3.5,0...
  this->chassisPosPID->set_deadband(3);
  this->chassisGyroPID = new pid(2.75,0.0,80.0,0.0);//60
  //this->chassisGyroPID->set_toleranceI(25);
  this->chassisGyroPID->set_deadband(6);
  this->currPos.x = 0;
  this->currPos.y = 0;
  waypoints = new path(currPos);
};


void chassis::updatePos(){
  this->currPos.x = this->currPos.x + ticksToInches(((this->getLeftMotorAt(0)->get_count())-this->getLeftMotorAt(0)->get_prevCount()),this->wheelDiameter,this->getLeftMotorAt(0)->get_motorType());
  this->currPos.y = 0;
}
void chassis::generatePathTo(CartesianVector targetPos){
  this->waypoints->set_minStep(2);
  this->waypoints->fillWaypointList(this->currPos, targetPos, 7);
};
std::vector<motor*>* chassis::get_leftMotors(){
  return &this->leftMotors;
};
void chassis::set_leftMotors(std::vector<motor*> motors){
  this->leftMotors = motors;
};
std::vector<motor*>* chassis::get_rightMotors(){
  return &this->rightMotors;
};
void chassis::set_rightMotors(std::vector<motor*> motors){
  this->rightMotors = motors;
};
motor* chassis::getLeftMotorAt(int pos){
  return (this->leftMotors[pos]);
};
motor* chassis::getRightMotorAt(int pos){
  return (this->rightMotors[pos]);
}
CartesianVector chassis::get_currPos(){
  return this->currPos;
}
void chassis::set_currPos(double x, double y)
{
  this->currPos.x = x;
  this->currPos.y = y;
}
void chassis::addLeftMotor(int port, bool reverse){
  motor* leftMotor = new motor(port);
  leftMotor->set_Direction(reverse);
  leftMotor->set_type(TURBO);
  leftMotor->set_velPID(this->chassisVelPID);
  leftMotor->set_posPID(this->chassisPosPID);
  leftMotor->set_address(0);
  // this->leftMotors.resize(this->leftMotors.size() + 1);
  this->leftMotors.push_back(leftMotor);
};

void chassis::addRightMotor(int port, bool reverse){
  motor* rightMotor = new motor(port);
  rightMotor->set_Direction(reverse);
  rightMotor->set_type(TURBO);
  rightMotor->set_velPID(this->chassisVelPID);
  rightMotor->set_posPID(this->chassisPosPID);
  rightMotor->set_imeReversed(true);
  rightMotor->set_address(1);
  //this->rightMotors.resize(this->rightMotors.size() + 1);
  this->rightMotors.push_back(rightMotor);
}

void chassis::leftPower(int power){
    for(int x=0;x<(int)(this->leftMotors.size());x++) {
      this->leftMotors[x]->set_Power(power);
    }

};

void chassis::rightPower(int power){
    for(int x=0;x<(int)(this->rightMotors.size());x++) {
      this->rightMotors[x]->set_Power(power);
    }

};

void chassis::leftVelocity(Encoder* enc, int vel){
//  if(leftMotors[0]->get_velocity(encoderGet(enc)) != vel){
    for(int x=0;x<(int)(this->leftMotors.size());x++) {
      this->leftMotors[x]->velocityControl(enc, vel);
    }
//  }
};

void chassis::rightVelocity(Encoder* enc, int vel){
    for(int x=0;x<(int)(this->rightMotors.size());x++) {
      this->rightMotors[x]->velocityControl(enc, vel);
    }
};

void chassis::leftVelocity(int vel){
//  if(leftMotors[0]->get_velocity(encoderGet(enc)) != vel){
    for(int x=0;x<(int)(this->leftMotors.size());x++) {
      this->leftMotors[x]->velocityControlIME(vel);
    }
//  }
};

void chassis::rightVelocity(int vel){
    for(int x=0;x<(int)(this->rightMotors.size());x++) {
      this->rightMotors[x]->velocityControlIME(vel);
    }
};

//
void chassis::leftPosition(int posInch){
printf("leftPos: %d\n",this->leftMotors[0]->get_count());
//  double posDeg;
  for(int x=0;x<(int)(this->leftMotors.size());x++){
  //posDeg = inchesToDeg(posInch, (double)(this->wheelDiameter), this->leftMotors[x]->get_motorType());
  //printf("posDeg: %f \n", posDeg);
  this->leftMotors[x]->positionControlIME(posInch);
  }
};

void chassis::rightPosition(int posInch){
//  double posDeg = 0;
  printf("rightPos: %d\n",this->rightMotors[0]->get_count());
  for(int x=0;x<(int)(this->rightMotors.size());x++){
  //  posDeg = inchesToDeg(posInch, (double)(this->wheelDiameter), this->leftMotors[x]->get_motorType());
    this->rightMotors[x]->positionControlIME(posInch);
  }
};

void chassis::haltLeft(){
  for(std::vector<motor>::size_type i = 0; i != this->leftMotors.size(); i++) {
    this->leftMotors[i]->set_Power(0);
  }

};

void chassis::haltRight(){
  for(std::vector<motor>::size_type i = 0; i != this->rightMotors.size(); i++) {
    this->rightMotors[i]->set_Power(0);
  }
};

bool atPos = false;
void chassis::moveDistance(float inch){
  atPos = false;
  leftPosition(inch);
  rightPosition(inch);
  if(abs(this->getLeftMotorAt(0)->get_posPID()->get_error()) <  this->getLeftMotorAt(0)->get_posPID()->get_deadband()){
    leftPower(0);
    rightPower(0);
    atPos = true;
  }
}


void chassis::moveToPos(CartesianVector vector){
  double deltaX = vector.x - this->currPos.x;
  double deltaY = vector.y - this->currPos.y;
  int length = (int)(sqrt(pow(abs(deltaX),2)+pow(abs(deltaY),2)));
  leftPosition(length);
  rightPosition(length);
  if(abs(length) <  this->getLeftMotorAt(0)->get_posPID()->get_deadband()){
    leftPower(0);
    rightPower(0);
    atPos = true;
  }
};

bool atGyro = false;
void chassis::spinToAngle(int targetAngle, analogSensors* gyro){
  atGyro = false;
  targetAngle = targetAngle/2;
	float difference = (targetAngle - (float)gyro->gyro_val());
  printf("%f\n", difference);
		if(abs(difference) > this->chassisGyroPID->get_deadband())// || time1[T1] > 500)
		{
			  difference = (targetAngle - (float)gyro->gyro_val());
        //calculate to see if it is faster to turn left or right
        if(difference > 180)
        {
                difference -= 360;
        }
        if(difference < -180)
        {
                difference += 360;
        }
        int power = difference * this->chassisGyroPID->get_kP();

        power = power < -100 ? -100 : power;
        power = power > 100 ? 100 : power;
        if(power < 0 && power > -15)
        {
        	power = -15*this->chassisGyroPID->get_kP();
        }
        if(power > 0 && power<15)
        {
        	power = 15*this->chassisGyroPID->get_kP();
      	}

        leftPower(-power);
        rightPower(power);
		}
    else{
      haltLeft();
      haltRight();
  		atGyro = true;
    }
};

void chassis::turnRightToAngle(int targetAngle, analogSensors* gyro){
  atGyro = false;
  targetAngle = targetAngle;
	float difference = (targetAngle - (float)gyro->gyro_val());
  printf("%f\n", difference);
		if(abs(difference) > this->chassisGyroPID->get_deadband())// || time1[T1] > 500)
		{
			  difference = (targetAngle - (float)gyro->gyro_val());
        //calculate to see if it is faster to turn left or right
        if(difference > 180)
        {
                difference -= 360;
        }
        if(difference < -180)
        {
                difference += 360;
        }
        int power = difference * this->chassisGyroPID->get_kP();

        power = power < -100 ? -100 : power;
        power = power > 100 ? 100 : power;
        if(power < 0 && power > -15)
        {
        	power = -10*this->chassisGyroPID->get_kP();
        }
        if(power > 0 && power<15)
        {
        	power = 15*this->chassisGyroPID->get_kP();
      	}

        haltLeft();
        rightPower(power);
		}
    else{
      haltLeft();
      haltRight();
  		atGyro = true;
    }
};
void chassis::turnLeftToAngle(int targetAngle, analogSensors* gyro){
  atGyro = false;
  targetAngle = targetAngle;
	float difference = (targetAngle - (float)gyro->gyro_val());
  printf("%f\n", difference);
		if(abs(difference) > this->chassisGyroPID->get_deadband())// || time1[T1] > 500)
		{
			  difference = (targetAngle - (float)gyro->gyro_val());
        //calculate to see if it is faster to turn left or right
        if(difference > 180)
        {
                difference -= 360;
        }
        if(difference < -180)
        {
                difference += 360;
        }
        int power = difference * this->chassisGyroPID->get_kP();

        power = power < -100 ? -100 : power;
        power = power > 100 ? 100 : power;
        if(power < 0 && power > -15)
        {
        	power = -15*this->chassisGyroPID->get_kP();
        }
        if(power > 0 && power<15)
        {
        	power = 15*this->chassisGyroPID->get_kP();
      	}

        haltRight();
        leftPower(-power);
		}
    else{
      haltLeft();
      haltRight();
  		atGyro = true;
    }
};

//unfinished, robot gives inconsistent values
void chassis::driveToLine(int power, analogSensors* leftLine, analogSensors* rightLine){
  power = power/abs(power);
  if(leftLine->get_leftLineSensorVal() < 250){
    leftPower(power*.5*(350-leftLine->get_leftLineSensorVal()));
  }
  else{
    haltLeft();
  }
  if(rightLine->get_rightLineSensorVal() < 250){
    rightPower(power*.5*(350-rightLine->get_rightLineSensorVal()));
  }
  else
  {
    haltRight();
  }
};
int chassis::get_wheelDiameter(){
  return this->wheelDiameter;
};

void chassis::set_wheelDiameter(int dia){
  this->wheelDiameter = dia;
};

path* chassis::get_waypoints(){
  return this->waypoints;
}
