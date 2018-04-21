
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
#include "vector.h"
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
    robot();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////this function will often be changed and is at the top///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setupCSUN1();
void setupCSUN2();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////Setters and Getters///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    state get_state();
    void set_communications(i2c communications);
    i2c* get_communications();
    void set_remote(control remote);
    control* get_remote();
    void set_drive(chassis drive);
    chassis* get_drive();
    void set_analog(analogSensors analog);
    analogSensors* get_analog();
    void set_digital(digitalSensors digital);
    digitalSensors* get_digital();
    void set_arm(lift arm);
    lift* get_arm();
    void set_ef(roller ef);
    roller* get_ef();
    int get_stackedCones();
    int get_targetStack();
    bool get_mobileGoalStatus();
    void set_mobileGoalStatus(bool mobileGoalStatus);

    void set_targetStack(int coneHeight);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void remoteListen();
    void joystickInputs();
    void leftJoystick();
    void rightJoystick();
    void rollerButtons();

    void autoAbort();

    bool addReleased = false;
    bool addPressed = false;
    bool subtractPressed = false;
    bool subtractReleased = false;
    void autonLiftProcess();
    void bigLift();

    bool toggleUp = true;
<<<<<<< HEAD
    void smallLift(){
      // motorSet(5, speed);
      if(this->remote->smallLiftToggle() ){
        this->arm->secondaryLiftPower(-100);
        // if(this->analog->get_potentiometerVal() < 1800){
        //   toggleUp = false;
        // }
        delay(50);
      }
      else if(this->remote->smallLiftToggleUp()){
        this->arm->secondaryLiftPower(100);
        // if(this->analog->get_potentiometerVal() > 3000 ){
        //   toggleUp = true;
        // }
        delay(50);
      }
      else{
        this->arm->haltSecondaryLift();
      }
    };
=======
    void smallLift();
>>>>>>> 4a831f2023e237a8e2d7d430b063411dcf627159

    void goalLift();

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

    void resetGyro();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////Routines related to movement will belong here////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lowerGoalLift();

void raiseGoalLift();

void driveIn(float inch);

void spinToAngle(int targetAngle);
void turnLeftToAngle(int targetAngle);
void turnRightToAngle(int targetAngle);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define SECONDARY_BOT  400
#define SECONDARY_TOP 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeight = 3; //change between 3 and height of loading station at 45


void setPreloadHeight();

void scorePreload();
//set to true for loading in the preLoad area. false for picking up cones from the ground
<<<<<<< HEAD
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
              this->arm->primaryLiftPosition(primaryBottomHeight,  (int)average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
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
            this->arm->primaryLiftPosition(primaryBottomHeight,   (int)average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));

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

            this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1),   (int)average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));

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
              this->arm->primaryLiftPosition(primaryBottomHeight + CONE_HEIGHT,   (int)average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
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
=======
void set_primaryBottomHeight(bool toPreLoad);

void autoLoad();
>>>>>>> 4a831f2023e237a8e2d7d430b063411dcf627159
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CSUN 2 AUTO LOAD CODE////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SECONDARY_BOT_CSUN2  400
#define SECONDARY_TOP_CSUN2 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeightCSUN2 = 3; //change between 3 and height of loading station at 45

//set to true for loading in the preLoad area. false for picking up cones from the ground
<<<<<<< HEAD
void set_primaryBottomHeightCSUN2(bool toPreLoad){
  if(toPreLoad){
    primaryBottomHeightCSUN2 = 47;
  }
  else{
    primaryBottomHeightCSUN2 = 3;
  }
};

    void autoLoadCSUN2(){
      // if(this->stackedCones == this->targetStack){
      //   autoStacking = false;
      //   addReleased = false;
      //   addPressed = false;
      //   subtractPressed = false;
      //   subtractReleased = false;
      // }
      // if(this->stackedCones < this->targetStack && this->stackedCones < MAX_HEIGHT){
      //   switch(robotState){
      //
      //         case ADJUSTHEIGHT:
      //           //Lower Secondary Lift to Lowest Position
      //           this->ef->halt();
      //           if(primaryBottomHeightCSUN2 == 47 && CONE_HEIGHT*(this->stackedCones) < primaryBottomHeightCSUN2){
      //             this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //             if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeightCSUN2){
      //                 robotState = BOTTOM;
      //                 this->ef->set_Power(-100);
      //                 this->arm->haltPrimaryLift();
      //                 this->arm->haltSecondaryLift();
      //             }
      //           }
      //           else{
      //             this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //             this->arm->secondaryLiftPosition(SECONDARY_BOT_CSUN2, this->analog->get_potentiometerVal());
      //             if(this->analog->get_potentiometerVal() < SECONDARY_BOT_CSUN2){
      //                 robotState = BOTTOM;
      //                 this->ef->set_Power(-100);
      //                 this->arm->haltPrimaryLift();
      //                 this->arm->haltSecondaryLift();
      //             }
      //
      //           }
      //
      //         break;
      //         case BOTTOM:
      //           //Move Primary lift to lowest position
      //           if(this->stackedCones > 2){ //if the cone stack gets to high, lower the speed to drop a bit so it doesn't damage the bot
      //             this->arm->set_primaryLiftPosPID(5.0,0.0,0.0);
      //           }
      //           this->ef->set_Power(-100);
      //           this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //
      //           this->arm->secondaryLiftPosition(SECONDARY_BOT_CSUN2, this->analog->get_potentiometerVal());
      //           if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) <= primaryBottomHeightCSUN2 && this->analog->get_potentiometerVal() < SECONDARY_BOT_CSUN2){
      //             robotState = INTAKE;
      //             this->arm->set_primaryLiftPosPID(10.5,0.0,0.0);
      //             this->arm->haltPrimaryLift();
      //             this->arm->haltSecondaryLift();
      //           }
      //         break;
      //
      //         case INTAKE:
      //           //Intake Cone
      //           // if(this->analog->get_potentiometerVal() > SECONDARY_BOT_CSUN2 || average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > 7){
      //           //   robotState = BOTTOM;
      //           // }
      //           // if(this->digital->get_leftLimitSwitch() == 0 || this->digital->get_rightLimitSwitch() == 0){
      //              robotState = CONEHEIGHT;
      //           //   this->ef->halt();
      //           // }
      //         break;
      //         //this is a change
      //         case CONEHEIGHT:
      //           //Raise Primary Lift to correct height (10deg/cone)
      //
      //           this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //
      //           this->ef->halt();
      //           //Raise Secondary Lift to correct height
      //             if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones-1)){
      //                 this->arm->secondaryLiftPosition(SECONDARY_TOP_CSUN2, this->analog->get_potentiometerVal());
      //             }
      //
      //           if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > CONE_HEIGHT*(this->stackedCones+1) && this->analog->get_potentiometerVal() > SECONDARY_TOP_CSUN2){
      //             robotState = OUTTAKE;
      //             this->arm->haltSecondaryLift();
      //             this->arm->haltPrimaryLift();
      //             delay(500);
      //           }
      //         break;
      //
      //         case OUTTAKE:
      //           //Outtake
      //           this->ef->set_Power(75);
      //           delay(400);
      //           this->stackedCones++;
      //           this->ef->halt();
      //           robotState = ADJUSTHEIGHT;
      //         break;
      //
      //         case RESTABOVE:
      //
      //           this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
      //           this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //           if(this->analog->get_potentiometerVal() < SECONDARY_BOT)
      //           {
      //             this->arm->haltSecondaryLift();
      //             this->arm->primaryLiftPosition(primaryBottomHeight + CONE_HEIGHT, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
      //             if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeight+CONE_HEIGHT)
      //             {
      //                 robotState = ADJUSTHEIGHT;
      //                 this->stackedCones++;
      //                 this->arm->haltPrimaryLift();
      //                 this->arm->haltSecondaryLift();
      //             }
      //           }
      //         break;
      //       };
      //     };
        };
=======
void set_primaryBottomHeightCSUN2(bool toPreLoad);

void autoLoadCSUN2();

>>>>>>> 4a831f2023e237a8e2d7d430b063411dcf627159
};

#endif
