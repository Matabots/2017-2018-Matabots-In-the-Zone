class controller{
public:
  controller(){
      //setup all controller bindings here

  }
  //return functions here

    int rightJoystickVal(){
      return joystickGetAnalog(2, ACCEL_Y);
    };
    int leftJoystickVal(){
      return joystickGetAnalog(1, ACCEL_Y);
    };

    int absRightJoystickVal() {
      return (joystickGetAnalog(2, ACCEL_Y) < 0 ? -joystickGetAnalog(2, ACCEL_Y) : joystickGetAnalog(2, ACCEL_Y));
    }
    int absLeftJoystickVal() {
      return (joystickGetAnalog(1, ACCEL_Y) < 0 ? -joystickGetAnalog(1, ACCEL_Y) : joystickGetAnalog(1, ACCEL_Y));
    }
    // int clawVal(){
    //   // return joystickGetDigital();
    // };
};
