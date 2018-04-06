
#ifndef ROBOT_H
#define ROBOT_H
#include "analogSensors.h"
#include "digitalSensors.h"
#include "chassis.h"
#include "lift.h"
#include "control.h"
#include "claw.h"
#include "roller.h"
#include "i2c.h"
#include <vector>
#include "motor.h"
#include "./utility/vector.h"
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
    roller* ef;
    i2c* communications;
    motor* aMotor;
    state robotState;
    subState robotSubState;
    int stackedCones;
  public:
    //default constructor to allocate memory
    robot(){
      this->drive = new chassis();
      this->analog = new analogSensors();
      this->digital = new digitalSensors();
      this->arm = new lift();
      this->ef = new roller();
      this->remote = new control(6, 7, 5, 8);
      this->communications = new i2c();
      this->aMotor = new motor();
      this->robotState = INIT;
      this->robotSubState = BOTTOM;
      stackedCones = 0;
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////this function will often be changed and is at the top///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup(){
      //add motors, sensors, reset values for sensors here
  ///////////////////////////////////////////
  ////////////// BEA (OLD) ////////////////////////
      // this->analog->set_gyro(analog8, 0);
      // this->analog->set_potentiometer(analog2);
      // this->digital->set_RightEncoder(digital2, digital3, false);
      // this->digital->set_LiftEncoder(digital11, digital12, false);
      // this->digital->set_LeftEncoder(digital8, digital9, true);
      // this->digital->set_coneLiftEncoder(digital4, digital5, false);
      // this->drive->addLeftMotor(motor2, false);
      // this->drive->addLeftMotor(motor8, false);
      // this->drive->addRightMotor(motor3, true);
      // this->drive->addRightMotor(motor9, false);
      // this->arm->addPrimaryLift(motor7, false);
      // this->arm->addPrimaryLift(motor6, true);
      // this->arm->addSecondaryLift(motor5, false);
      // this->ef->set_Port(motor4);
      // this->ef->set_Direction(false);

  ///////////////////////////////////////////
  ////////////// CSUN1 Carbon  ////////////////////////
      this->analog->set_gyro(analog8, 0);
      this->analog->set_potentiometer(analog2);
      this->digital->set_limitSwitch(digital5);
      this->digital->set_leftLiftEncoder(digital3, digital4, false);
      this->digital->set_rightLiftEncoder(digital11, digital12, true);
      //this->digital->set_LeftEncoder(digital8, digital9, true);
      // this->digital->set_coneLiftEncoder(digital4, digital5, false);
      this->drive->addLeftMotor(motor2, false);
      this->drive->addLeftMotor(motor3, true);
      this->drive->addRightMotor(motor8, false);
      this->drive->addRightMotor(motor9, true);
      this->arm->addPrimaryLift(motor4, false);
      this->arm->addPrimaryLift(motor7, true);
      this->arm->addSecondaryLift(motor6, true);
      this->arm->addGoalLift(motor1, true);
      this->arm->addGoalLift(motor10, false);
      this->ef->addRoller(motor5, true);
      ///////////////////////////////////////////
      ////////////// CSUN2  ////////////////////////
      //Dinero add your setup code here

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
    void set_ef(roller ef){
      this->ef = &ef;
    };
    roller* get_ef(){
      return this->ef;
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void remoteListen(){
      joystickInputs();
      rollerButtons();
      bigLift();
      smallLift();
      goalLift();
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
    void rollerButtons(){
      if(this->remote->rollerOpen()){
        this->ef->set_Power(100);
        delay(50);
      }else if(this->remote->rollerClose()){
        this->ef->set_Power(-100);
        delay(50);
      }else{
        this->ef->halt();
      }
    };
    void bigLift(){
      if(this->remote->bigLiftUp()){
        this->arm->primaryLiftPower(100);
        delay(50);
      }else if(this->remote->bigLiftDown()){
        this->arm->primaryLiftPower(-100);
        delay(50);
      }else{
        this->arm->haltPrimaryLift();
      }
    };
    void smallLift(){
      // motorSet(5, speed);
      if(this->remote->smallLiftUp()){
        this->arm->secondaryLiftPower(-100);
        delay(50);
      }else if(this->remote->smallLiftDown()){
        this->arm->secondaryLiftPower(100);
        delay(50);
      }else{
        this->arm->haltSecondaryLift();
      }
    };
    void goalLift(){
      if(this->remote->goalLiftUp()){
        this->arm->goalLiftPower(100);
      }else if(this->remote->goalLiftDown()){
        this->arm->goalLiftPower(-100);
        delay(50);
      }else{
        this->arm->haltGoalLift();
      }
    }

  // void smallLift(){
  //     if(this->remote->smallLiftUp()){
  //       this->arm->groupTwoPower(100);
  //       delay(50);
  //     }else if(this->remote->smallLiftDown()){
  //       this->arm->groupTwoPower(-100);
  //       delay(50);
  //     }else{
  //       this->arm->haltGroupTwo();
  //     }
  //   };
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void runRobot(){
    switch(robotState){
      case INIT:

      break;
      case TURN:


      break;
      case MOVE:
        this->drive->moveToPos(this->drive->get_waypoints()->get_waypointAt(0));
      break;
      case MGOAL: //make sure the mobile goal is in place
        this->arm->goalLiftPower(-127);
        if(this->arm->get_goalLiftAt(0)->get_count() < 5){
          robotState = AUTOLOAD;
          this->arm->haltGoalLift();
        }
      break;
      case AUTOLOAD:
        switch(robotSubState){
          case BOTTOM:
            //Move Primary lift to lowest position
            this->arm->primaryLiftPosition(0, this->digital->leftLiftEncoderVal());
            //Lower Secondary Lift to Lowest Position
            //this->arm->secondaryLiftPosition(0,)
            if(this->digital->leftLiftEncoderVal() <= 2){
              robotSubState = INTAKE;
              this->arm->haltPrimaryLift();
            }
          break;

          case INTAKE:
            //Intake Cone
            this->ef->set_Power(100);
            if(this->digital->get_limitSwitch() == 1){
              robotSubState = CONEHEIGHT;
              this->ef->halt();
            }
          break;

          case CONEHEIGHT:
            //Raise Primary Lift to correct height (10deg/cone)
            this->arm->primaryLiftPosition(12*(stackedCones+1), this->digital->leftLiftEncoderVal());
            //Raise Secondary Lift to correct height
            if(this->digital->leftLiftEncoderVal() >= 12*(stackedCones+1)){
              robotSubState = OUTTAKE;
              this->arm->haltPrimaryLift();
            }

          break;

          case OUTTAKE:
            //Outtake
            this->ef->set_Power(-100);
            delay(1000);
            robotSubState = CONEHEIGHT;
            this->ef->halt();
          break;
      };
      break;

    };
};

};
#endif
