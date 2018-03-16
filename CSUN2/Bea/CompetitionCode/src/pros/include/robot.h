
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
    //private variables (raw pointers)
    analogSensors* analog;
    digitalSensors* digital;
    chassis* drive;
    lift* arm;
    control* remote;
    claw* ef;
    i2c* communications;
  public:
    //default constructor to allocate memory
    robot(){
      this->drive = new chassis();
      this->analog = new analogSensors();
      this->digital = new digitalSensors();
      this->arm = new lift();
      this->ef = new claw();
      this->remote = new control(6, 5, 8);
      this->communications = new i2c();
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////this function will often be changed and is at the top///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
      //add motors, sensors, reset values for sensors here
      this->analog->set_gyro(analog8, 0);
      this->analog->set_potentiometer(analog2);
      this->digital->set_RightEncoder(digital2, digital3, false);
      this->digital->set_LiftEncoder(digital11, digital12, false);
      this->digital->set_LeftEncoder(digital7, digital8, false);
      this->digital->set_coneLiftEncoder(digital4, digital5, false);
      this->drive->addLeftMotor(motor2, false);
      this->drive->addLeftMotor(motor8, false);
      this->drive->addRightMotor(motor3, true);
      this->drive->addRightMotor(motor9, false);
      this->arm->addGroupOne(motor7, false);
      this->arm->addGroupOne(motor6, true);
      this->arm->addGroupTwo(motor5, false);
      this->ef->set_Port(motor4);
      this->ef->set_Direction(false);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////Setters and Getters///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void set_communications(i2c communications){
      this->communications = &communications;
    };
    i2c* get_communications(){
      return this->communications;
    };
    void set_remote(control remote){
      this->remote = &remote;
    };
    control* get_remote(){
      return this->remote;
    };
    void set_drive(chassis drive){
      this->drive = &drive;
    };
    chassis* get_drive(){
      return this->drive;
    };
    void set_analog(analogSensors analog){
      this->analog = &analog;
    };
    analogSensors* get_analog(){
      return this->analog;
    };
    void set_digital(digitalSensors digital){
      this->digital = &digital;
    };
    digitalSensors* get_digital(){
      return this->digital;
    };
    void set_arm(lift arm){
      this->arm = &arm;
    };
    lift* get_arm(){
      return this->arm;
    };
    void set_ef(claw ef){
      this->ef = &ef;
    };
    claw* get_ef(){
      return this->ef;
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void remoteListen(){
      joystickInputs();
      clawButtons();
      bigLift();
      smallLift();
    };
    void joystickInputs(){
      rightJoystick();
      leftJoystick();
    };
    void leftJoystick(){
      if(this->remote->absLeftJoystickVal()>15){
  			this->drive->leftPower(this->remote->leftJoystickVal());
  		}else{
  			this->drive->haltLeft();
  		}
    };
    void rightJoystick(){
      if(this->remote->absRightJoystickVal()>15){
  			this->drive->rightPower(this->remote->rightJoystickVal());
  		}else{
  			this->drive->haltRight();
  		}
    };
    void clawButtons(){
      if(this->remote->clawOpen()){
        this->ef->set_Power(100);
        delay(50);
      }else if(this->remote->clawClose()){
        this->ef->set_Power(-100);
        delay(50);
      }else{
        this->ef->halt();
      }
    };
    void bigLift(){
      if(this->remote->bigLiftUp()){
        this->arm->groupOnePower(100);
        delay(50);
      }else if(this->remote->bigLiftDown()){
        this->arm->groupOnePower(-100);
        delay(50);
      }else{
        this->arm->haltGroupOne();
      }
    };
    void smallLift(){
      // motorSet(5, speed);
      if(this->remote->smallLiftUp()){
        this->arm->groupTwoPower(-100);
        delay(50);
      }else if(this->remote->smallLiftDown()){
        this->arm->groupTwoPower(100);
        delay(50);
      }else{
        this->arm->haltGroupTwo();
      }
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Routines related to sensors will belong here////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void resetGyro(){
      int previousValue = 0;
      this->analog->reset_gyro();
      this->analog->set_deltaGyro(0);
      this->drive->leftPower(0);
      this->drive->rightPower(0);
      previousValue = this->analog->gyro_val();
      delay(2000);
      this->analog->set_deltaGyro(this->analog->gyro_val() - previousValue);
    };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Routines related to movement will belong here////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


      //PID HERE

};
#endif
