
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
#include "botUart.h"
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
    bool hasMobileGoal;
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
      this->hasMobileGoal = false;
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////this function will often be changed and is at the top///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setupCSUN1(){
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
      this->digital->set_leftLimitSwitch(digital5);
      this->digital->set_rightLimitSwitch(digital6);
      this->analog->set_leftLineSensor(analog2);
      this->analog->set_rightLineSensor(analog3);
      this->digital->set_leftLiftEncoder(digital3, digital4, false);
      this->digital->set_rightLiftEncoder(digital11, digital12, true);
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

      imeReset(0);
      imeReset(1);
      imeReset(2);
};
void setupCSUN2(){
      //add motors, sensors, reset values for sensors here

      // this->analog->set_gyro(analog8, 0);
      //this->analog->set_potentiometer(analog1);
      // this->digital->set_leftLimitSwitch(digital5);
      // this->digital->set_rightLimitSwitch(digital6);
      // this->analog->set_leftLineSensor(analog2);
      // this->analog->set_rightLineSensor(analog3);
      this->digital->set_rightLiftEncoder(digital7, digital8, false);
      this->digital->set_leftLiftEncoder(digital5, digital6, false);
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

      imeReset(0);
      imeReset(1);
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
    };
    int get_targetStack(){
      return this->targetStack;
    };
    bool get_mobileGoalStatus(){
      return this->hasMobileGoal;
    };
    void set_mobileGoalStatus(bool mobileGoalStatus){
      this->hasMobileGoal = mobileGoalStatus;
    };

    void set_targetStack(int coneHeight){
      this->targetStack = coneHeight;
    };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void remoteListen(){
      joystickInputs();
      autonLiftProcess();
      autoAbort();
      printf("Remote Listening\n");
      // this->uartComms->runUART();
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
        //this->arm->secondaryLiftPower(0);
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
        // if(this->analog->get_potentiometerVal() < 1800){
        //   toggleUp = false;
        // }
        delay(50);
      }
      // else if(this->remote->smallLiftToggle()){
      //   this->arm->secondaryLiftPower(100);
      //   // if(this->analog->get_potentiometerVal() > 3000 ){
      //   //   toggleUp = true;
      //   // }
      //   delay(50);
      // }
      else{
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

void lowerGoalLift(){
  while(!this->arm->atBottom){
  this->arm->goalLiftDown();
  }
};

void raiseGoalLift(){
  while(!this->arm->atTop){
    this->arm->goalLiftUp();
  }
};

void driveIn(float inch)
{
imeReset(0);
imeReset(1);
  this->drive->atPos = false;
  while (!this->drive->atPos) {
    this->drive->moveDistance(inch);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};

void spinToAngle(int targetAngle)
{
imeReset(0);
imeReset(1);
  this->drive->atGyro = false;
  while(!this->drive->atGyro){
  this->drive->spinToAngle(targetAngle, this->analog);
  printf("yaw: %d\n", this->analog->gyro_val());
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
void turnLeftToAngle(int targetAngle){
  imeReset(0);
  imeReset(1);
  this->drive->atGyro = false;
  while(!this->drive->atGyro){
    this->drive->turnLeftToAngle(targetAngle, this->analog);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
void turnRightToAngle(int targetAngle){
  this->drive->atGyro = false;
  imeReset(0);
  imeReset(1);
  while(!this->drive->atGyro){
    this->drive->turnRightToAngle(targetAngle, this->analog);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define SECONDARY_BOT  400
#define SECONDARY_TOP 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeight = 3; //change between 3 and height of loading station at 45


void setPreloadHeight(){
  while(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) < CONE_HEIGHT+5)
  {
    this->arm->primaryLiftPosition(CONE_HEIGHT+5, this->digital->leftLiftEncoderVal());
  }

  this->arm->haltPrimaryLift();
};

void scorePreload(){
  this->ef->set_Power(75);
  delay(400);
  this->stackedCones++;
  this->ef->halt();
  this->ef->halt();
};
//set to true for loading in the preLoad area. false for picking up cones from the ground
void set_primaryBottomHeight(bool toPreLoad){
  if(toPreLoad){
    primaryBottomHeight = 47;
  }
  else{
    primaryBottomHeight = 3;
  }
};

void autoLoad(){
  if(this->stackedCones == this->targetStack){
    autoStacking = false;
    addReleased = false;
    addPressed = false;
    subtractPressed = false;
    subtractReleased = false;
  }
  if(this->stackedCones < this->targetStack && this->stackedCones < MAX_HEIGHT){
    switch(robotState){

          case ADJUSTHEIGHT:
            //Lower Secondary Lift to Lowest Position
            this->ef->halt();
            if(primaryBottomHeight == 47 && CONE_HEIGHT*(this->stackedCones) < primaryBottomHeight){
              this->arm->primaryLiftPosition(primaryBottomHeight, this->digital->leftLiftEncoderVal());
              if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeight){
                  robotState = BOTTOM;
                  this->ef->set_Power(-100);
                  this->arm->haltPrimaryLift();
                  this->arm->haltSecondaryLift();
              }
            }
            else{
              this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
              if(this->analog->get_potentiometerVal() < SECONDARY_BOT){
                  robotState = BOTTOM;
                  this->ef->set_Power(-100);
                  this->arm->haltPrimaryLift();
                  this->arm->haltSecondaryLift();
              }

            }

          break;
          case BOTTOM:
            //Move Primary lift to lowest position
            if(this->stackedCones > 2){ //if the cone stack gets to high, lower the speed to drop a bit so it doesn't damage the bot
              this->arm->set_primaryLiftPosPID(5.0,0.0,0.0);
            }
            this->ef->set_Power(-100);
            this->arm->primaryLiftPosition(primaryBottomHeight, this->digital->leftLiftEncoderVal());

            this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
            if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) <= primaryBottomHeight && this->analog->get_potentiometerVal() < SECONDARY_BOT){
              robotState = INTAKE;
              this->arm->set_primaryLiftPosPID(10.5,0.0,0.0);
              this->arm->haltPrimaryLift();
              this->arm->haltSecondaryLift();
            }
          break;

          case INTAKE:
            //Intake Cone
            // if(this->analog->get_potentiometerVal() > SECONDARY_BOT || average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > 7){
            //   robotState = BOTTOM;
            // }
            if(this->digital->get_leftLimitSwitch() == 0 || this->digital->get_rightLimitSwitch() == 0){
              robotState = CONEHEIGHT;
              this->ef->halt();
            }
          break;
          //this is a change
          case CONEHEIGHT:
            //Raise Primary Lift to correct height (10deg/cone)

            this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), this->digital->leftLiftEncoderVal());

            this->ef->halt();
            //Raise Secondary Lift to correct height
              if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones-1)){
                  this->arm->secondaryLiftPosition(SECONDARY_TOP, this->analog->get_potentiometerVal());
              }

            if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones+1) && this->analog->get_potentiometerVal() > SECONDARY_TOP){
              robotState = OUTTAKE;
              this->arm->haltSecondaryLift();
              this->arm->haltPrimaryLift();
              delay(500);
            }
          break;

          case OUTTAKE:
            //Outtake
            this->ef->set_Power(75);
            delay(400);
            this->ef->halt();
            robotState = RESTABOVE;
          break;
          case RESTABOVE:

            this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
            if(this->analog->get_potentiometerVal() < SECONDARY_BOT)
            {
              this->arm->primaryLiftPosition(primaryBottomHeight + CONE_HEIGHT, this->digital->leftLiftEncoderVal());
              if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeight+ CONE_HEIGHT)
              {
                  robotState = ADJUSTHEIGHT;
                  this->stackedCones++;
                  this->arm->haltPrimaryLift();
                  this->arm->haltSecondaryLift();
              }
            }
          break;
        };
      };
    };
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CSUN 2 AUTO LOAD CODE////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SECONDARY_BOT_CSUN2  400
#define SECONDARY_TOP_CSUN2 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeightCSUN2 = 3; //change between 3 and height of loading station at 45

//set to true for loading in the preLoad area. false for picking up cones from the ground
void set_primaryBottomHeightCSUN2(bool toPreLoad){
  if(toPreLoad){
    primaryBottomHeightCSUN2 = 47;
  }
  else{
    primaryBottomHeightCSUN2 = 3;
  }
};

    void autoLoadCSUN2(){
      if(this->stackedCones == this->targetStack){
        autoStacking = false;
        addReleased = false;
        addPressed = false;
        subtractPressed = false;
        subtractReleased = false;
      }
      if(this->stackedCones < this->targetStack && this->stackedCones < MAX_HEIGHT){
        switch(robotState){

              case ADJUSTHEIGHT:
                //Lower Secondary Lift to Lowest Position
                this->ef->halt();
                if(primaryBottomHeightCSUN2 == 47 && CONE_HEIGHT*(this->stackedCones) < primaryBottomHeightCSUN2){
                  this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, this->digital->leftLiftEncoderVal());
                  if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeightCSUN2){
                      robotState = BOTTOM;
                      this->ef->set_Power(-100);
                      this->arm->haltPrimaryLift();
                      this->arm->haltSecondaryLift();
                  }
                }
                else{
                  this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones), this->digital->leftLiftEncoderVal());
                  this->arm->secondaryLiftPosition(SECONDARY_BOT_CSUN2, this->analog->get_potentiometerVal());
                  if(this->analog->get_potentiometerVal() < SECONDARY_BOT_CSUN2){
                      robotState = BOTTOM;
                      this->ef->set_Power(-100);
                      this->arm->haltPrimaryLift();
                      this->arm->haltSecondaryLift();
                  }

                }

              break;
              case BOTTOM:
                //Move Primary lift to lowest position
                if(this->stackedCones > 2){ //if the cone stack gets to high, lower the speed to drop a bit so it doesn't damage the bot
                  this->arm->set_primaryLiftPosPID(5.0,0.0,0.0);
                }
                this->ef->set_Power(-100);
                this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, this->digital->leftLiftEncoderVal());

                this->arm->secondaryLiftPosition(SECONDARY_BOT_CSUN2, this->analog->get_potentiometerVal());
                if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) <= primaryBottomHeightCSUN2 && this->analog->get_potentiometerVal() < SECONDARY_BOT_CSUN2){
                  robotState = INTAKE;
                  this->arm->set_primaryLiftPosPID(10.5,0.0,0.0);
                  this->arm->haltPrimaryLift();
                  this->arm->haltSecondaryLift();
                }
              break;

              case INTAKE:
                //Intake Cone
                // if(this->analog->get_potentiometerVal() > SECONDARY_BOT_CSUN2 || average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > 7){
                //   robotState = BOTTOM;
                // }
                // if(this->digital->get_leftLimitSwitch() == 0 || this->digital->get_rightLimitSwitch() == 0){
                   robotState = CONEHEIGHT;
                //   this->ef->halt();
                // }
              break;
              //this is a change
              case CONEHEIGHT:
                //Raise Primary Lift to correct height (10deg/cone)

                this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), this->digital->leftLiftEncoderVal());

                this->ef->halt();
                //Raise Secondary Lift to correct height
                  if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones-1)){
                      this->arm->secondaryLiftPosition(SECONDARY_TOP_CSUN2, this->analog->get_potentiometerVal());
                  }

                if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones+1) && this->analog->get_potentiometerVal() > SECONDARY_TOP_CSUN2){
                  robotState = OUTTAKE;
                  this->arm->haltSecondaryLift();
                  this->arm->haltPrimaryLift();
                  delay(500);
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

              case RESTABOVE:

                this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
                if(this->analog->get_potentiometerVal() < SECONDARY_BOT)
                {
                  this->arm->haltSecondaryLift();
                  this->arm->primaryLiftPosition(primaryBottomHeight + CONE_HEIGHT, this->digital->leftLiftEncoderVal());
                  if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeight+CONE_HEIGHT)
                  {
                      robotState = ADJUSTHEIGHT;
                      this->stackedCones++;
                      this->arm->haltPrimaryLift();
                      this->arm->haltSecondaryLift();
                  }
                }
              break;
            };
          };
        };
};

#endif
