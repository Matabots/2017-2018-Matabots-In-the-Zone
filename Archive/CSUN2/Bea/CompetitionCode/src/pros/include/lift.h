#ifndef LIFT_H
#define LIFT_H
#include "ports.h"
#include "motor.h"
#include <vector>
class lift{
private:
  std::vector<motor*> groupOne;
  std::vector<motor*> groupTwo;

public:

  lift(){

  };
  std::vector<motor*> get_groupOne(){
    return this->groupOne;
  };
  void set_groupOne(std::vector<motor*> motors){
    this->groupOne = motors;
  };
  std::vector<motor*> get_groupTwo(){
    return this->groupTwo;
  };
  void set_groupTwo(std::vector<motor*> motors){
    this->groupTwo = motors;
  };
  void addGroupOne(int port, bool reverse){
    motor* liftMotor = new motor(port);
    liftMotor->set_Direction(reverse);
    // this->groupOne.resize(this->groupOne.size() + 1);
    this->groupOne.push_back(liftMotor);
  };

  void addGroupTwo(int port, bool reverse){
    motor* liftMotor = new motor(port);
    liftMotor->set_Direction(reverse);
    // this->groupTwo.resize(this->groupTwo.size() + 1);
    this->groupTwo.push_back(liftMotor);
  };

  void groupOnePower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->groupOne.size(); i++) {
      this->groupOne[i]->set_Power(power);
    };
  };

  void groupTwoPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->groupTwo.size(); i++) {
      this->groupTwo[i]->set_Power(power);
    };
  };

  void haltGroupOne(){
    for(std::vector<motor*>::size_type i = 0; i != this->groupOne.size(); i++) {
      this->groupOne[i]->set_Power(0);
    };
  };

  void haltGroupTwo(){
    for(std::vector<motor*>::size_type i = 0; i != this->groupTwo.size(); i++) {
      this->groupTwo[i]->set_Power(0);
    };
  };
};
#endif
