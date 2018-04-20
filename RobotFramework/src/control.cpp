#include "control.h"

control::control(int autonLift, int autonAbort, int clearStacked, int bigLift, int smallLift, int goalLift, int roller){
    //setup all controller bindings here
    this->bigLift = bigLift;
    this->smallLift = smallLift; //8R toggle
    this->clearStack = clearStacked;//8L wipe the stack
    this->goalLifter = goalLift; //7U up 7d down
    this->roller = roller; //toggle buttons intake 8u 8d outtake
    this->autonLift = autonLift;
    this->autonAbort = autonAbort; //7right
    //7 left to set loading position
  };
//return functions here
  int control::autonLiftProcessAdd(){
    return joystickGetDigital(1, this->autonLift, JOY_UP);
  };
  int control::autonLiftProcessSubtract(){
    return joystickGetDigital(1, this->autonLift, JOY_DOWN);
  };
  int control::autoLiftAbort(){
    return joystickGetDigital(1, this->autonAbort, JOY_RIGHT);
  }
  int control::rollerOpen(){
    return joystickGetDigital(1, this->roller, JOY_DOWN);
  };
  int control::rollerClose(){
    return joystickGetDigital(1, this->roller, JOY_UP);
  };
  int control::smallLiftToggle(){
    return joystickGetDigital(1, this->smallLift, JOY_RIGHT);
  };
  int control::clearConeStack(){
    return joystickGetDigital(1, this->clearStack, JOY_LEFT);
  };
  int control::bigLiftUp(){
    return joystickGetDigital(1, this->bigLift, JOY_UP);
  };
  int control::bigLiftDown(){
    return joystickGetDigital(1, this->bigLift, JOY_DOWN);
  };
  int control::goalLiftUp(){
    return joystickGetDigital(1,this->goalLifter, JOY_UP);
  };
  int control::goalLiftDown(){
    return joystickGetDigital(1,this->goalLifter,JOY_DOWN);
  }
  int control::rightJoystickVal(){
    return joystickGetAnalog(1, 2);
  };
  int control::leftJoystickVal(){
    return joystickGetAnalog(1, 3);
  };

  int absRightJoystickVal() {
    return (joystickGetAnalog(1, 2) < 0 ? -joystickGetAnalog(1, 2) : joystickGetAnalog(1, 2));
  };
  int absLeftJoystickVal() {
    return (joystickGetAnalog(1, 3) < 0 ? -joystickGetAnalog(1, 3) : joystickGetAnalog(1, 3));
  };
