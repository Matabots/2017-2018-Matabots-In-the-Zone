#include "digitalSensors.h"
#include "analogSensors.h"
#include "robotChasis.h"
#include "i2c.h"
#include "controller.h"
#include "liftMotors.h"
#include "robotClaw.h"
#include "ports.h"

class robot{
  private:
    analogSensors analog;
    digitalSensors digital;
    robotChasis drive;
    liftMotors lift;
    i2c communications;
    controller remote;
    robotClaw claw;

  public:
    robot(){

    };
    void set_analog(){
       analog =  analogSensors();
    };
    void set_digital(){
      digital = digitalSensors();
    };
    void set_drive(){
      drive = robotChasis();
    };
    robotChasis get_drive(){
      return drive;
    };
    void set_lift(){
      lift = liftMotors();
    };
    void set_communications(){
      communications = i2c();
    };
    void set_remote(){
      remote = controller();
    };
    void set_claw(){
      claw = robotClaw();
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
