#ifndef CONTROL_H
#define CONTROL_H
#include "API.h"
class control{
private:
    int bigLift;
    int smallLift;
    int goalLifter;
    int roller;
public:
  control(int bigLift, int smallLift, int goalLift, int roller){
      //setup all controller bindings here
      this->bigLift = bigLift;
      this->smallLift = smallLift;
      this->goalLifter = goalLift;
      this->roller = roller;
    };
  //return functions here
    int rollerOpen(){
      return joystickGetDigital(1, this->roller, JOY_UP);
    };
    int rollerClose(){
      return joystickGetDigital(1, this->roller, JOY_DOWN);
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

    int absRightJoystickVal() {
      return (joystickGetAnalog(1, 2) < 0 ? -joystickGetAnalog(1, 2) : joystickGetAnalog(1, 2));
    };
    int absLeftJoystickVal() {
      return (joystickGetAnalog(1, 3) < 0 ? -joystickGetAnalog(1, 3) : joystickGetAnalog(1, 3));
    };

};
#endif
