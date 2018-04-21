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

  lift();
  std::vector<motor*> get_primaryLift();
  void set_primaryLift(std::vector<motor*> motors);
  std::vector<motor*> get_secondaryLift();
  void set_secondaryLift(std::vector<motor*> motors);
  std::vector<motor*> get_goalLift();
  motor* get_goalLiftAt(int x);
  void set_goalLift(std::vector<motor*> motors);
  void addPrimaryLift(int port, bool reverse);

<<<<<<< HEAD
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
    motor* liftMotor = new motor(port,9.5,0.0,0.0,0.0);//10.5
    liftMotor->set_Direction(reverse);
    liftMotor->set_type(ENC);
    liftMotor->get_posPID()->set_deadband(1);
    //liftMotor->get_posPID()->set_deadband(3);
    this->primaryLift.push_back(liftMotor);
  };
=======
  void addSecondaryLift(int port, bool reverse);
>>>>>>> 4a831f2023e237a8e2d7d430b063411dcf627159

  void addGoalLift(int port, bool reverse);

void set_primaryLiftPosPID(double kP, double kI, double kD, double kF=0);

  void primaryLiftPower(int power);

  void primaryLiftPosition(int deg, int encoderVal);

  void secondaryLiftPosition(int targetCount, int potentiometer);

  bool atTop = true;
  bool atBottom = false;
  void goalLiftUp();
  void goalLiftDown();

  void secondaryLiftPower(int power);

  void goalLiftPower(int power);
  void haltPrimaryLift();

  void haltSecondaryLift();

  void haltGoalLift();
};
#endif
