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
  std::vector<motor*> goalLift;

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
  std::vector<motor*> get_goalLift(){
    return this->goalLift;
  }
  motor* get_goalLiftAt(int x){
    return this->goalLift[x];
  }
  void set_goalLift(std::vector<motor*> motors){
    this->goalLift = motors;
  }
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

  void addGoalLift(int port, bool reverse){
    motor* goalMotor = new motor(port);
    goalMotor->set_Direction(reverse);
    goalMotor->set_type(TORQUE);
    goalMotor->set_address(2);
    this->goalLift.push_back(goalMotor);
  }
  void primaryLiftPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->set_Power(power);
    }
  };

  void primaryLiftPosition(int deg, int encoderVal){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      if(encoderVal < deg){
        this->primaryLift[i]->set_Power(100);
      }
      else if(encoderVal > deg){
        this->primaryLift[i]->set_Power(-100);
      }
      else{
        this->primaryLift[i]->set_Power(0);
      }
    }
  };
  void secondaryLiftPosition(int targetCount, int potentiometer){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      if(abs(potentiometer) < targetCount){
        this->secondaryLift[i]->set_Power(-50);
      }
      else if(abs(potentiometer) > targetCount){
        this->secondaryLift[i]->set_Power(75);
      }
      else{
        haltSecondaryLift();
      }
    }
  };

  void secondaryLiftPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      this->secondaryLift[i]->set_Power(power);
    }
  };

  void goalLiftPower(int power){
    for(std::vector<motor*>::size_type i =0; i != this->goalLift.size();i++){
      this->goalLift[i]->set_Power(power);
    }
  };
  void haltPrimaryLift(){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->set_Power(0);
    }
  };

  void haltSecondaryLift(){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      this->secondaryLift[i]->set_Power(0);
    }
  };

  void haltGoalLift(){
    for(std::vector<motor*>::size_type i = 0;i != this->goalLift.size(); i++){
      this->goalLift[i]->set_Power(0);
    }
  };
};
#endif
