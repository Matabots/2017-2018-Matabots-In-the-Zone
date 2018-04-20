
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
    robot();
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////this function will often be changed and is at the top///////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup();
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
    void smallLift();

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
void set_primaryBottomHeight(bool toPreLoad);

void autoLoad();
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SECONDARY_BOT_CSUN2  400
#define SECONDARY_TOP_CSUN2 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeightCSUN2 = 3; //change between 3 and height of loading station at 45

//set to true for loading in the preLoad area. false for picking up cones from the ground
void set_primaryBottomHeightCSUN2(bool toPreLoad);

void autoLoadCSUN2();
};

#endif
