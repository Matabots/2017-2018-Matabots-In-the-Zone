
#ifndef ROBOT_H
#define ROBOT_H
#include "analogSensors.h"
#include "digitalSensors.h"
#include "chassis.h"
#include "lift.h"
#include "control.h"
#include "claw.h"
#include "i2c.h"
#include <vector>
#include "motor.h"
#include "ports.h"
#include "potentiometer.h"
class robot{
  private:
    analogSensors analog;
    digitalSensors digital;
    chassis drive;
    lift arm;
    control remote;
    claw ef;
    i2c communications;
  public:
    robot(){
      this->drive = chassis();
      this->analog = analogSensors();
      this->digital = digitalSensors();
      this->arm = lift();
      this->ef = claw();
      this->remote = control();
      this->communications = i2c();
    };
    void set_communications(i2c communications){
      this->communications = communications;
    };
    i2c get_communications(){
      return this->communications;
    };
    void set_remote(control remote){
      this->remote = remote;
    };
    control get_remote(){
      return this->remote;
    };
    void set_drive(chassis drive){
      this->drive = drive;
    };
    chassis get_drive(){
      return this->drive;
    };
    void set_analog(analogSensors analog){
      this->analog = analog;
    };
    analogSensors get_analog(){
      return this->analog;
    };
    void set_digital(digitalSensors digital){
      this->digital = digital;
    };
    digitalSensors get_digital(){
      return this->digital;
    };
    void set_arm(lift arm){
      this->arm = arm;
    };
    lift get_arm(){
      return this->arm;
    };
    void set_ef(claw ef){
      this->ef = ef;
    };
    claw get_ef(){
      return this->ef;
    };
    void joystickInputs(){
      rightJoystick();
      leftJoystick();
    };
    void leftJoystick(){
      if(this->remote.absRightJoystickVal()>0){
  			this->drive.rightPower(this->remote.rightJoystickVal());
  		}else{
  			this->drive.haltRight();
  		}
    };
    void rightJoystick(){
      if(this->remote.absRightJoystickVal()>0){
  			this->drive.rightPower(this->remote.rightJoystickVal());
  		}else{
  			this->drive.haltRight();
  		}
    };
};
#endif
