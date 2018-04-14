#ifndef CHASSIS_H
#define CHASSIS_H

#include "ports.h"
#include "motor.h"
#include "math.h"
#include <vector>
#include "path.h"
#include "analogSensors.h"
#define vSAMPLE_PERIOD 100  //Sample period for digital control
class chassis{
private:
  std::vector<motor*> leftMotors;
  std::vector<motor*> rightMotors;
  int wheelDiameter;
  float gearRatio;
  pid* chassisVelPID;
  pid* chassisPosPID;
  pid* chassisGyroPID;
  path* waypoints;
  CartesianVector currPos;
public:

  chassis(){
    this->wheelDiameter = 4; //inches
    //this->chassisVelPID = new pid(10,3.48,896.9,0.0);
    this->chassisVelPID = new pid(1.5,0.0,0.0,0.0);
    //this->chassisPosPID = new pid(0.45,0.0,0.0125,0.0);//4.0,0,0
                            //0.45                      //0.85,0,0 for gyro turn
    // this->chassisPosPID = new pid(0.85,0.024,0.016,0.0);
    // this->chassisPosPID->set_deadband(10);
    this->chassisPosPID = new pid(3.5,0.00,0.0,0.0);
    this->chassisPosPID->set_deadband(3);
    this->chassisGyroPID = new pid(0.85,0.0,0.0,0.0);
    this->chassisGyroPID->set_deadband(5);
    this->currPos.x = 0;
    this->currPos.y = 0;
    waypoints = new path(currPos);
  };


  void updatePos(){
    this->currPos.x = this->currPos.x + ticksToInches(((this->getLeftMotorAt(0)->get_count())-this->getLeftMotorAt(0)->get_prevCount()),this->wheelDiameter,this->getLeftMotorAt(0)->get_motorType());
    this->currPos.y = 0;
  }
  void generatePathTo(CartesianVector targetPos){
    this->waypoints->set_minStep(2);
    this->waypoints->fillWaypointList(this->currPos, targetPos, 7);
  };
  std::vector<motor*> get_leftMotors(){
    return this->leftMotors;
  };
  void set_leftMotors(std::vector<motor*> motors){
    this->leftMotors = motors;
  };
  std::vector<motor*> get_rightMotors(){
    return this->rightMotors;
  };
  void set_rightMotors(std::vector<motor*> motors){
    this->rightMotors = motors;
  };
  motor* getLeftMotorAt(int pos){
    return (this->leftMotors[pos]);
  };
  motor* getRightMotorAt(int pos){
    return (this->rightMotors[pos]);
  }
  CartesianVector get_currPos(){
    return this->currPos;
  }
  void set_currPos(double x, double y)
  {
    this->currPos.x = x;
    this->currPos.y = y;
  }
  void addLeftMotor(int port, bool reverse){
    motor* leftMotor = new motor(port);
    leftMotor->set_Direction(reverse);
    leftMotor->set_type(TURBO);
    leftMotor->set_velPID(this->chassisVelPID);
    leftMotor->set_posPID(this->chassisPosPID);
    leftMotor->set_address(0);
    // this->leftMotors.resize(this->leftMotors.size() + 1);
    this->leftMotors.push_back(leftMotor);
  };

  void addRightMotor(int port, bool reverse){
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

  void leftPower(int power){
      for(int x=0;x<(int)(this->leftMotors.size());x++) {
        this->leftMotors[x]->set_Power(power);
      }

  };

  void rightPower(int power){
      for(int x=0;x<(int)(this->rightMotors.size());x++) {
        this->rightMotors[x]->set_Power(power);
      }

  };

  void leftVelocity(Encoder* enc, int vel){
  //  if(leftMotors[0]->get_velocity(encoderGet(enc)) != vel){
      for(int x=0;x<(int)(this->leftMotors.size());x++) {
        this->leftMotors[x]->velocityControl(enc, vel);
      }
  //  }
  };

  void rightVelocity(Encoder* enc, int vel){
      for(int x=0;x<(int)(this->rightMotors.size());x++) {
        this->rightMotors[x]->velocityControl(enc, vel);
      }
  };

  void leftVelocity(int vel){
  //  if(leftMotors[0]->get_velocity(encoderGet(enc)) != vel){
      for(int x=0;x<(int)(this->leftMotors.size());x++) {
        this->leftMotors[x]->velocityControlIME(vel);
      }
  //  }
  };

  void rightVelocity(int vel){
      for(int x=0;x<(int)(this->rightMotors.size());x++) {
        this->rightMotors[x]->velocityControlIME(vel);
      }
  };

  //
  void leftPosition(int posInch){
  printf("leftPos: %d\n",this->leftMotors[0]->get_count());
  //  double posDeg;
    for(int x=0;x<(int)(this->leftMotors.size());x++){
    //posDeg = inchesToDeg(posInch, (double)(this->wheelDiameter), this->leftMotors[x]->get_motorType());
    //printf("posDeg: %f \n", posDeg);
    this->leftMotors[x]->positionControlIME(posInch);
    }
  };

  void rightPosition(int posInch){
  //  double posDeg = 0;
    printf("rightPos: %d\n",this->rightMotors[0]->get_count());
    for(int x=0;x<(int)(this->rightMotors.size());x++){
    //  posDeg = inchesToDeg(posInch, (double)(this->wheelDiameter), this->leftMotors[x]->get_motorType());
      this->rightMotors[x]->positionControlIME(posInch);
    }
  };

  void haltLeft(){
    for(std::vector<motor>::size_type i = 0; i != this->leftMotors.size(); i++) {
      this->leftMotors[i]->set_Power(0);
    }

  };

  void haltRight(){
    for(std::vector<motor>::size_type i = 0; i != this->rightMotors.size(); i++) {
      this->rightMotors[i]->set_Power(0);
    }
  };

  void moveToPos(CartesianVector vector){
    double deltaX = vector.x - this->currPos.x;
    double deltaY = vector.y - this->currPos.y;
    int length = (int)(sqrt(pow(abs(deltaX),2)+pow(abs(deltaY),2)));
    leftPosition(length);
    rightPosition(length);
    if(abs(length) <  this->getLeftMotorAt(0)->get_posPID()->get_deadband()){
      leftPower(0);
      rightPower(0);
    }
  };

  bool atGyro = false;
  void turnToAngle(int targetAngle, analogSensors* gyro){
  	float difference = (targetAngle - (float)gyro->gyro_val());
    printf("%f", difference);
  	//	time1[T1] =0;
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
          if(abs(difference)>this->chassisGyroPID->get_deadband())
          {
          	//time1[T1] =0;
          }
          int power = difference * this->chassisGyroPID->get_kP();

          power = power < -100 ? -100 : power;
          power = power > 100 ? 100 : power;
          if(power < 0 && power > -25)
          {
          	power = -25*this->chassisGyroPID->get_kP();
          }
          if(power > 0 && power<25)
          {
          	power = 25*this->chassisGyroPID->get_kP();
        	}

          leftPower(-power);
          rightPower(power);
  		}
  		atGyro = true;
  };

  int get_wheelDiameter(){
    return this->wheelDiameter;
  };

  void set_wheelDiameter(int dia){
    this->wheelDiameter = dia;
  };

  path* get_waypoints(){
    return this->waypoints;
  }
};
#endif
