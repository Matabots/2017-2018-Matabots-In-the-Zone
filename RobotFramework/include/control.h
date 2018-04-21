#ifndef CONTROL_H
#define CONTROL_H
#include "API.h"
class control{
private:
    int autonLift;
    int autonAbort;
    int bigLift;
    int smallLift;
    int goalLifter;
    int roller;
    int clearStack;
public:
  control(int autonLift, int autonAbort, int clearStacked, int bigLift, int smallLift, int goalLift, int roller);
  //return functions here
<<<<<<< HEAD
    int autonLiftProcessAdd(){
      return joystickGetDigital(1, this->autonLift, JOY_UP);
    };
    int autonLiftProcessSubtract(){
      return joystickGetDigital(1, this->autonLift, JOY_DOWN);
    };
    int autoLiftAbort(){
      return joystickGetDigital(1, this->autonAbort, JOY_RIGHT);
    }
    int rollerOpen(){
      return joystickGetDigital(1, this->roller, JOY_DOWN);
    };
    int rollerClose(){
      return joystickGetDigital(1, this->roller, JOY_UP);
    };
    int smallLiftToggle(){
      return joystickGetDigital(1, this->smallLift, JOY_RIGHT);
    };
    int smallLiftToggleUp(){
      return joystickGetDigital(1, this->smallLift, JOY_LEFT);
    };
    int clearConeStack(){
      return joystickGetDigital(1, this->clearStack, JOY_LEFT);
    };
    int bigLiftUp(){
      return joystickGetDigital(1, this->bigLift, JOY_UP);
    };
    int bigLiftDown(){
      return joystickGetDigital(1, this->bigLift, JOY_DOWN);
    };
    int goalLiftUp(){
      return joystickGetDigital(1,this->goalLifter, JOY_UP);
    };
    int goalLiftDown(){
      return joystickGetDigital(1,this->goalLifter,JOY_DOWN);
    }
    int rightJoystickVal(){
      return joystickGetAnalog(1, 2);
    };
    int leftJoystickVal(){
      return joystickGetAnalog(1, 3);
    };
=======
    int autonLiftProcessAdd();
    int autonLiftProcessSubtract();
    int autoLiftAbort();
    int rollerOpen();
    int rollerClose();
    int smallLiftToggle();
    int clearConeStack();
    int bigLiftUp();
    int bigLiftDown();
    int goalLiftUp();
    int goalLiftDown();
    int rightJoystickVal();
    int leftJoystickVal();
>>>>>>> 4a831f2023e237a8e2d7d430b063411dcf627159

    int absRightJoystickVal();
    int absLeftJoystickVal();

};
#endif
