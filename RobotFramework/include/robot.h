
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
#include "../include/uart.h"
#include "uart.h"
#include "utility.h"
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
    int stackedCones;
    botUart* uartComms;
    int targetStack;
  public:
  bool autoStacking = false;
    //default constructor to allocate memory
    robot(){
      this->drive = new chassis();
      this->analog = new analogSensors();
      this->digital = new digitalSensors();
      this->arm = new lift();
      this->ef = new roller();
      this->remote = new control(6, 7, 8, 5, 8, 7, 8);
      this->communications = new i2c();
      this->aMotor = new motor();
      this->robotState = ADJUSTHEIGHT;
      this->stackedCones = 0;
      this->targetStack = 0;
      this->uartComms = new botUart();
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
      this->analog->set_potentiometer(analog1);
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
    state get_state(){
      return this->robotState;
    }
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
    int get_stackedCones(){
      return this->stackedCones;
    }
    int get_targetStack(){
      return this->targetStack;
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void remoteListen(){
      joystickInputs();
      autonLiftProcess();
      autoAbort();
      this->uartComms->runUART();
      if(!autoStacking){
        rollerButtons();
        bigLift();
        smallLift();
        goalLift();
      }
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

    void autoAbort(){
      if(this->remote->autoLiftAbort()){
        autoStacking = false;
        addReleased = false;
        addPressed = false;
        subtractPressed = false;
        subtractReleased = false;
        this->robotState = ADJUSTHEIGHT;
        this->targetStack = this->stackedCones;
        this->arm->primaryLiftPower(0);
        this->ef->set_Power(0);
        this->arm->secondaryLiftPower(0);
      }
    }

    bool addReleased = false;
    bool addPressed = false;
    bool subtractPressed = false;
    bool subtractReleased = false;
    void autonLiftProcess(){
      if(!autoStacking){
        printf("this is running");
        if(this->remote->autonLiftProcessAdd()){
          addPressed = true;
        }
        if(!this->remote->autonLiftProcessAdd()){
          addReleased = true;
        }
        if(this->remote->autonLiftProcessSubtract()){
          subtractPressed = true;
        }
        if(!this->remote->autonLiftProcessSubtract()){
          subtractReleased = true;
        }
        if(addPressed && addReleased && this->targetStack < 8){
          this->targetStack += 1;
          autoStacking = true;
        }
        if(subtractPressed && subtractReleased && this->stackedCones > 0 ){
          this->targetStack -= 1;
          this->stackedCones -=1;
          autoStacking = true;
        }
      }
      else{
        printf("lift is running");
        autoLoad();
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
    bool toggleUp = true;
    void smallLift(){
      // motorSet(5, speed);
      if(this->remote->smallLiftToggle() ){
        this->arm->secondaryLiftPower(-100);
        if(this->analog->get_potentiometerVal() < 1800){
          toggleUp = false;
        }
        delay(50);
      }
      else if(this->remote->smallLiftToggle()){
        this->arm->secondaryLiftPower(100);
        if(this->analog->get_potentiometerVal() > 3000 ){
          toggleUp = true;
        }
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

void autoLoad( ){
  if(this->stackedCones == this->targetStack){
    autoStacking = false;
    addReleased = false;
    addPressed = false;
    subtractPressed = false;
    subtractReleased = false;
  }
  if(this->stackedCones < this->targetStack && this->stackedCones < 8){
    switch(robotState){

          case ADJUSTHEIGHT:
            //Lower Secondary Lift to Lowest Position
            this->arm->primaryLiftPosition(10*(this->stackedCones), this->digital->leftLiftEncoderVal());
            this->arm->secondaryLiftPosition(1800, this->analog->get_potentiometerVal());
            if(this->analog->get_potentiometerVal() < 1800){
                robotState = BOTTOM;
                this->ef->set_Power(-100);
                this->arm->haltPrimaryLift();
                this->arm->haltSecondaryLift();
            }
          break;
          case BOTTOM:
            //Move Primary lift to lowest position
            if(this->stackedCones > 2){ //if the cone stack gets to high, lower the speed to drop a bit so it doesn't damage the bot
              this->arm->set_primaryLiftPosPID(2.0,0.0,0.0);
              printf("I should have changed");
            }
            this->ef->set_Power(-100);
            this->arm->primaryLiftPosition(3, this->digital->leftLiftEncoderVal());

            this->arm->secondaryLiftPosition(1800, this->analog->get_potentiometerVal());
            if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) <= 3 && this->analog->get_potentiometerVal() < 1800){
              robotState = INTAKE;
              this->arm->set_primaryLiftPosPID(9.0,0.0,0.0);
              this->arm->haltPrimaryLift();
              this->arm->haltSecondaryLift();
            }
          break;

          case INTAKE:
            //Intake Cone
            if(this->analog->get_potentiometerVal() > 1800){
              robotState = BOTTOM;
            }
            if(this->digital->get_limitSwitch() == 0){
              robotState = CONEHEIGHT;
              this->ef->halt();
            }
          break;
          //this is a change
          case CONEHEIGHT:
            //Raise Primary Lift to correct height (10deg/cone)

            this->arm->primaryLiftPosition(10*(this->stackedCones+1), this->digital->leftLiftEncoderVal());
            //Raise Secondary Lift to correct height
              if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= 10*(this->stackedCones-1)){
                  this->arm->secondaryLiftPosition(3000, this->analog->get_potentiometerVal());
              }

            if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= 10*(this->stackedCones+1) && this->analog->get_potentiometerVal() > 3000){
              robotState = OUTTAKE;
              this->arm->haltSecondaryLift();
              this->arm->haltPrimaryLift();
              delay(350);
            }
          break;

          case OUTTAKE:
            //Outtake
            this->ef->set_Power(75);
            delay(400);
            this->stackedCones++;
            this->ef->halt();
            robotState = ADJUSTHEIGHT;
          break;
        };
      };
    };
};

#endif
