#ifndef CHASSIS_H
#define CHASSIS_H

#include "ports.h"
#include "motor.h"
#include <vector>

#define vSAMPLE_PERIOD 100  //Sample period for digital control
class chassis{
private:
  std::vector<motor*> leftMotors;
  std::vector<motor*> rightMotors;
  int wheelDiameter;
  float gearRatio;
  pid* chassisPID;
public:

  chassis(){
    this->wheelDiameter = 4; //inches
    //this->chassisPID = new pid(10,3.48,896.9,0.0);
    this->chassisPID = new pid(2.0,0.0,0.0,0.0);
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
  void addLeftMotor(int port, bool reverse){
    motor* leftMotor = new motor(port);
    leftMotor->set_Direction(reverse);
    leftMotor->set_velPID(this->chassisPID);
    leftMotor->set_address(0);
    // this->leftMotors.resize(this->leftMotors.size() + 1);
    this->leftMotors.push_back(leftMotor);
  };

  void addRightMotor(int port, bool reverse){
    motor* rightMotor = new motor(port);
    rightMotor->set_Direction(reverse);
    rightMotor->set_velPID(this->chassisPID);
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

  int get_wheelDiameter(){
    return this->wheelDiameter;
  };

  void set_wheelDiameter(int dia){
    this->wheelDiameter = dia;
  };
};
#endif
