#ifndef CHASSIS_H
#define CHASSIS_H

#include "ports.h"
#include "motor.h"
#include <vector>

#define vP_GAIN 10.0 //gain for only proportinal controller
#define vPROPORTIONAL_GAIN 3.48 //PID controller proportinal
#define vINTEGRAL_CONST 896.9 //PID controller integral
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
    this->chassisPID = new pid(1.0,0.0,0.0,0.0);
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
  void addLeftMotor(int port, bool reverse){
    motor* leftMotor = new motor(port);
    leftMotor->set_Direction(reverse);
    leftMotor->set_velPID(this->chassisPID);
    // this->leftMotors.resize(this->leftMotors.size() + 1);
    this->leftMotors.push_back(leftMotor);
  };

  void addRightMotor(int port, bool reverse){
    motor* rightMotor = new motor(port);
    rightMotor->set_Direction(reverse);
    rightMotor->set_velPID(this->chassisPID);
    // this->rightMotors.resize(this->rightMotors.size() + 1);
    this->rightMotors.push_back(rightMotor);
  }

  void leftPower(int power){
    if(leftMotors[0]->get_Power() != power){
      for(int x=0;x<(int)(this->leftMotors.size());x++) {
        this->leftMotors[x]->set_Power(power);
      }
    }
  };

  void rightPower(int power){
    for(int x=0;x<(int)(this->rightMotors.size());x++) {
      this->rightMotors[x]->set_Power(power);
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
