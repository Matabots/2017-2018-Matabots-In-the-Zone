#ifndef CONTROL_H
#define CONTROL_H
#include "API.h"
class control{
private:
    int autonLift;
    int autonAbort;
    int smallLift;
    int goalLifter;
    int roller;
    int clearStack;
public:
  control(int autonLift, int autonAbort, int clearStacked, int smallLift, int goalLift, int roller);

    int autonLiftProcessAdd();
    int autonLiftProcessSubtract();
    int autoLiftAbort();
    int rollerOpen();
    int rollerClose();
    int clearConeStack();
    int bigLift();
    int goalLiftUp();
    int goalLiftDown();
    int rightJoystickVal();
    int leftJoystickVal();
    int smallLiftUp();
    int smallLiftDown();
    int absRightJoystickVal();
    int absLeftJoystickVal();

};
#endif
