#ifndef CLAW_H
#define CLAW_H
#include "motor.h"
class claw{
private:
  motor* clawMotor;
  // bool reversed;

public:

  claw(){
    this->clawMotor = new motor();
  }

  void set_Direction(bool reverse){
    this->clawMotor->set_Direction(reverse);
  };
  void set_Port(int port){
    this->clawMotor->set_Port(port);
  };
  void set_Power(int power){
    this->clawMotor->set_Power(power);
  };
  void halt(){
    this->clawMotor->set_Power(0);
  };
  bool get_Direction(){
    return this->clawMotor->get_Direction();
  };
  int get_Speed(){
    return this->clawMotor->get_Speed();
  };
  void set_ClawMotor(int port){
     this->clawMotor->set_Port(port);
  };
};
#endif
