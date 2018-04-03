#ifndef ROLLER_H
#define ROLLER

#include"motor.h"

class roller{
private:
  motor* rollerMotor;

public:
  roller(){
    this->rollerMotor = new motor();
  }

  void addRoller(int port, bool reverse){
    set_Port(port);
    set_Direction(reverse);
  };
  void set_Direction(bool reverse){
    this->rollerMotor->set_Direction(reverse);
  };
  void set_Port(int port){
    this->rollerMotor->set_Port(port);
  };
  void set_Power(int power){
    this->rollerMotor->set_Power(power);
  };
  void halt(){
    this->rollerMotor->set_Power(0);
  };
  bool get_Direction(){
    return this->rollerMotor->get_Direction();
  };
  int get_Speed(){
    return this->rollerMotor->get_Speed();
  };
  void set_ClawMotor(int port){
     this->rollerMotor->set_Port(port);
  };
};

#endif
