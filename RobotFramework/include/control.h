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

    int absRightJoystickVal();
    int absLeftJoystickVal();

};
#endif
