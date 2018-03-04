#include "digitalSensors.h"
#include "analogSensors.h"
#include "robotChasis.h"
#include "i2c.h"
#include "controller.h"
#include "liftMotors.h"
#include "robotClaw.h"
#include "ports.h"

class robot{
  public:
    analogSensors analog = analogSensors();
    digitalSensors digital = digitalSensors();
    robotChasis drive = robotChasis();
    liftMotors lift = liftMotors();
    i2c communications = i2c();
    controller remote = controller();
    robotClaw claw = robotClaw();
    robot(){

    };
    void joystickInputs(){
      rightJoystick();
      leftJoystick();
    };
    void leftJoystick(){
      if(remote.absRightJoystickVal()>0){
  			drive.rightPower(remote.rightJoystickVal());
  		}else{
  			drive.haltRight();
  		}
    };
    void rightJoystick(){
      if(remote.absRightJoystickVal()>0){
  			drive.rightPower(remote.rightJoystickVal());
  		}else{
  			drive.haltRight();
  		}
    };
};
