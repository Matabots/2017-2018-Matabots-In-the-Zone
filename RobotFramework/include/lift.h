#ifndef LIFT_H
#define LIFT_H
#include "ports.h"
#include "motor.h"
#include "API.h"
#include <vector>
class lift{
private:
  std::vector<motor*> primaryLift;
  std::vector<motor*> secondaryLift;

public:

  lift(){

  };
  std::vector<motor*> get_primaryLift(){
    return this->primaryLift;
  };
  void set_primaryLift(std::vector<motor*> motors){
    this->primaryLift = motors;
  };
  std::vector<motor*> get_secondaryLift(){
    return this->secondaryLift;
  };
  void set_secondaryLift(std::vector<motor*> motors){
    this->secondaryLift = motors;
  };
  void addPrimaryLift(int port, bool reverse){
    motor* liftMotor = new motor(port);
    liftMotor->set_Direction(reverse);
    // this->primaryLift.resize(this->primaryLift.size() + 1);
    this->primaryLift.push_back(liftMotor);
  };

  void addSecondaryLift(int port, bool reverse){
    motor* liftMotor = new motor(port);
    liftMotor->set_Direction(reverse);
    // this->secondaryLift.resize(this->secondaryLift.size() + 1);
    this->secondaryLift.push_back(liftMotor);
  }

  void primaryLiftPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->set_Power(power);
    }
  };

  void secondaryLiftPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      this->secondaryLift[i]->set_Power(power);
    }
  };

  void haltGroupOne(){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->set_Power(0);
    }
  };

  void haltGroupTwo(){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      this->secondaryLift[i]->set_Power(0);
    }
  };
};
#endif
