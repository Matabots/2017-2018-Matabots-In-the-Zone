#ifndef LIFT_H
#define LIFT_H
#include "ports.h"
#include "motor.h"
#include "API.h"
#include <vector>
class lift{
private:
  std::vector<motor*> primaryLift;
  pid* primaryLiftPosPID; //currently not being used. Things are being hard coded :(
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
    motor* liftMotor = new motor(port,10.5,0.0,0.0,0.0);
    liftMotor->set_Direction(reverse);
    liftMotor->set_type(ENC);
    liftMotor->get_posPID()->set_deadband(1);
    //liftMotor->get_posPID()->set_deadband(3);
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

void set_primaryLiftPosPID(double kP, double kI, double kD, double kF=0) {
  pid* posPID = new pid(kP,kI,kD,kF);
  for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
    this->primaryLift[i]->set_posPID(posPID);
  }
};

  void primaryLiftPower(int power){
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->set_Power(power);
    }
  };

  void primaryLiftPosition(int deg, int encoderVal){
    printf("kP: %f\n", this->primaryLift[0]->get_posPID()->get_kP());
    for(std::vector<motor*>::size_type i = 0; i != this->primaryLift.size(); i++) {
      this->primaryLift[i]->tickControl(deg,encoderVal);
    }
  };

  void secondaryLiftPosition(int targetCount, int potentiometer){
    for(std::vector<motor*>::size_type i = 0; i != this->secondaryLift.size(); i++) {
      if((potentiometer) > (targetCount)){
        this->secondaryLift[i]->set_Power(-70);
      }
      else if((potentiometer) < (targetCount)){
        this->secondaryLift[i]->set_Power((0.15*(targetCount-potentiometer)));
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
