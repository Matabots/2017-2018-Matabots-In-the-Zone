#ifndef CONTROL_H
#define CONTROL_H

class control{
private:
    int bigLift;
    int smallLift;
    int claw;
public:
  control(int bigLift, int smallLift, int claw){
      //setup all controller bindings here
      this->bigLift = bigLift;
      this->smallLift = smallLift;
      this->claw = claw;
    };
  //return functions here
    int clawOpen(){
      return joystickGetDigital(1, this->claw, JOY_UP);
    };
    int clawClose(){
      return joystickGetDigital(1, this->claw, JOY_RIGHT);
    };
    int smallLiftUp(){
      return joystickGetDigital(1, this->smallLift, JOY_UP);
    };
    int smallLiftDown(){
      return joystickGetDigital(1, this->smallLift, JOY_DOWN);
    };
    int bigLiftUp(){
      return joystickGetDigital(1, this->bigLift, JOY_UP);
    };
    int bigLiftDown(){
      return joystickGetDigital(1, this->bigLift, JOY_DOWN);
    };
    int rightJoystickVal(){
      return joystickGetAnalog(1, 2);
    };
    int leftJoystickVal(){
      return joystickGetAnalog(1, 3);
    };

    int absRightJoystickVal() {
      return (joystickGetAnalog(1, 2) < 0 ? -joystickGetAnalog(1, 2) : joystickGetAnalog(1, 2));
    };
    int absLeftJoystickVal() {
      return (joystickGetAnalog(1, 3) < 0 ? -joystickGetAnalog(1, 3) : joystickGetAnalog(1, 3));
    };

};
#endif
