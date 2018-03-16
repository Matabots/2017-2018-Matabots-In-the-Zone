#ifndef CHASSIS_H
#define CHASSIS_H

#include "ports.h"
#include "motor.h"
#include <vector>

class chassis{
private:
  std::vector<motor*> leftMotors;
  std::vector<motor*> rightMotors;
  int wheelDiameter;
public:

  chassis(){
    this->wheelDiameter = 4; //inches
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
    // this->leftMotors.resize(this->leftMotors.size() + 1);
    this->leftMotors.push_back(leftMotor);
  };

  void addRightMotor(int port, bool reverse){
    motor* rightMotor = new motor(port);
    rightMotor->set_Direction(reverse);
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
      printf("%d\n",this->rightMotors[x]->get_Port());
      printf("%d\n",this->rightMotors[x]->get_Power());
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
  int convertCountToInch(Encoder enc){
    int ticksPerRev = 360;
    return ((3.14*(this->wheelDiameter)*encoderGet(enc))/ticksPerRev);
  };
  int convertCountToInch(motor inputMotor){
    int ticksPerRev = 627;
    if(inputMotor.get_motorType() == TURBO){

    }
    return ((3.14*(this->wheelDiameter)*(inputMotor.get_count()))/ticksPerRev);
  };
};
#endif
