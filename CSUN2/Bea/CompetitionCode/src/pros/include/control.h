#ifndef CONTROL_H
#define CONTROL_H

class control{
private:
  int num;
public:
  control(){
      //setup all controller bindings here
      num = 0;
    };
  //return functions here

    int rightJoystickVal(){
      return joystickGetAnalog(2, ACCEL_Y);
    };
    int leftJoystickVal(){
      return joystickGetAnalog(1, ACCEL_Y);
    };

    int absRightJoystickVal() {
      return (joystickGetAnalog(2, ACCEL_Y) < 0 ? -joystickGetAnalog(2, ACCEL_Y) : joystickGetAnalog(2, ACCEL_Y));
    };
    int absLeftJoystickVal() {
      return (joystickGetAnalog(1, ACCEL_Y) < 0 ? -joystickGetAnalog(1, ACCEL_Y) : joystickGetAnalog(1, ACCEL_Y));
    };
};
#endif
