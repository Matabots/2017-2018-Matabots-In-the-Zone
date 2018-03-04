class controller{
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
    int clawVal(){
      // return joystickGetDigital();
    }
};
