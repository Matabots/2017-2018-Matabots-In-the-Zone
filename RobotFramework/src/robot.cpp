#include "robot.h"
    //default constructor to allocate memory

    robot::robot(){
      this->drive = new chassis();
      this->analog = new analogSensors();
      this->digital = new digitalSensors();
      this->arm = new lift();
      this->ef = new roller();
      this->remote = new control();
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
void robot::setupCSUN1(){
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
      this->remote->setupcontrol(8, 7, 8, 5, 5, 6, 6, 1);
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
void robot::setupCSUN2(){
      //add motors, sensors, reset values for sensors here
      this->remote->setupcontrol(6, 7, 8, 5, 8, 5, 8, 2);
      this->analog->set_gyro(analog8, 0);
      this->analog->set_potentiometer(analog1);
      this->digital->set_leftLimitSwitch(digital4);
      this->digital->set_rightLiftEncoder(digital7, digital8, true);
      this->digital->set_leftLiftEncoder(digital5, digital6, true);
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
    state robot::get_state(){
      return this->robotState;
    }
    void robot::set_communications(i2c communications){
      this->communications = &communications;
    };
    i2c* robot::get_communications(){
      return this->communications;
    };
    void robot::set_remote(control remote){
      this->remote = &remote;
    };
    control* robot::get_remote(){
      return this->remote;
    };
    void robot::set_drive(chassis drive){
      this->drive = &drive;
    };
    chassis* robot::get_drive(){
      return this->drive;
    };
    void robot::set_analog(analogSensors analog){
      this->analog = &analog;
    };
    analogSensors* robot::get_analog(){
      return this->analog;
    };
    void robot::set_digital(digitalSensors digital){
      this->digital = &digital;
    };
    digitalSensors* robot::get_digital(){
      return this->digital;
    };
    void robot::set_arm(lift arm){
      this->arm = &arm;
    };
    lift* robot::get_arm(){
      return this->arm;
    };
    void robot::set_ef(roller ef){
      this->ef = &ef;
    };
    roller* robot::get_ef(){
      return this->ef;
    };
    int robot::get_stackedCones(){
      return this->stackedCones;
    };
    int robot::get_targetStack(){
      return this->targetStack;
    };
    bool robot::get_mobileGoalStatus(){
      return this->hasMobileGoal;
    };
    void robot::set_mobileGoalStatus(bool mobileGoalStatus){
      this->hasMobileGoal = mobileGoalStatus;
    };

    void robot::set_targetStack(int coneHeight){
      this->targetStack = coneHeight;
    };
    long robot::get_IntakeTimer(){
        return this->intakeTimer;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////These are the operator control functions////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void robot::remoteListen(){
      joystickInputs();
      autonLiftProcess();
      autoAbort();
      printf("Remote Listening\n");
      if(!autoStacking){
        rollerButtons();
        bigLift();
        smallLift();
        goalLift();
      }
    };
    void robot::uart()
    {
      this->uartComms->runUART();
    }
    void robot::joystickInputs(){
      rightJoystick();
      leftJoystick();
    };
    void robot::leftJoystick(){
      if(this->remote->absLeftJoystickVal()>15){
  			this->drive->leftPower(this->remote->leftJoystickVal());
  		}else{
  			this->drive->haltLeft();
  		}
    };
    void robot::rightJoystick(){
      if(this->remote->absRightJoystickVal()>15){
  			this->drive->rightPower(this->remote->rightJoystickVal());
  		}else{
  			this->drive->haltRight();
  		}
    };
    void robot::rollerButtons(){
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

    void robot::autoAbort(){
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
    };

    bool addReleased = false;
    bool addPressed = false;
    bool subtractPressed = false;
    bool subtractReleased = false;
    void robot::autonLiftProcess(){
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
    void robot::bigLift(){
      if(abs(this->remote->bigLift()) > 20){
        this->arm->primaryLiftPower(this->remote->bigLift());
        delay(50);
      }else{
        this->arm->haltPrimaryLift();
      }
    };

    bool toggleUp = true;
    void robot::smallLift(){
      // motorSet(5, speed);
      if(this->remote->smallLiftUp() ){
        this->arm->secondaryLiftPower(100);
        // if(this->analog->get_potentiometerVal() < 1800){
        //   toggleUp = false;
        // }
        delay(50);
      }
      else if(this->remote->smallLiftDown()){
        this->arm->secondaryLiftPower(-100);
        // if(this->analog->get_potentiometerVal() > 3000 ){
        //   toggleUp = true;
        // }
        delay(50);
      }
      else{
        this->arm->haltSecondaryLift();
      }
    };

    void robot::goalLift(){
      if(this->remote->goalLiftUp()){
        this->arm->goalLiftPower(100);
      }else if(this->remote->goalLiftDown()){
        this->arm->goalLiftPower(-100);
        delay(50);
      }else{
        this->arm->haltGoalLift();
      }
    };

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

    void robot::resetGyro(){
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

void robot::lowerGoalLift(){
  while(!this->arm->atBottom){
  this->arm->goalLiftDown();
  delay(50);
  }
};

void robot::raiseGoalLift(){
  while(!this->arm->atTop){
    this->arm->goalLiftUp();
    delay(50);
  }
};

void robot::driveIn(float inch)
{
imeReset(0);
imeReset(1);
  this->drive->atPos = false;
  while (!this->drive->atPos) {
    this->drive->moveDistance(inch);
    delay(50);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};

void robot::spinToAngle(int targetAngle)
{
imeReset(0);
imeReset(1);
  this->drive->atGyro = false;
  while(!this->drive->atGyro){
  this->drive->spinToAngle(targetAngle, this->analog);
  printf("yaw: %d\n", this->analog->gyro_val());
  delay(50);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
void robot::turnLeftToAngle(int targetAngle){
  imeReset(0);
  imeReset(1);
  this->drive->atGyro = false;
  while(!this->drive->atGyro){
    this->drive->turnLeftToAngle(targetAngle, this->analog);
    delay(50);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
void robot::turnRightToAngle(int targetAngle){
  this->drive->atGyro = false;
  imeReset(0);
  imeReset(1);
  while(!this->drive->atGyro){
    this->drive->turnRightToAngle(targetAngle, this->analog);
    delay(50);
  }
  this->drive->haltLeft();
  this->drive->haltRight();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#define SECONDARY_BOT  400
#define SECONDARY_TOP 1500
#define CONE_HEIGHT 10
#define MAX_HEIGHT 8
int primaryBottomHeight = 1; //change between 3 and height of loading station at 45
long intakeTimer =0;


void robot::setPreloadHeight(){
  while(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) < CONE_HEIGHT+5)
  {
    this->arm->primaryLiftPosition(CONE_HEIGHT, this->digital->leftLiftEncoderVal());
  }

  this->arm->haltPrimaryLift();
};

void robot::scorePreload(){
  this->ef->set_Power(75);
  delay(400);
  this->stackedCones++;
  this->ef->halt();
  this->ef->halt();
};
//set to true for loading in the preLoad area. false for picking up cones from the ground
void robot::set_primaryBottomHeight(bool toPreLoad){
  if(toPreLoad){
    primaryBottomHeight = 40;
  }
  else{
    primaryBottomHeight = 1;
  }
};

void robot::autoLoad(){
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
            if(primaryBottomHeight == 40 && CONE_HEIGHT*(this->stackedCones) < primaryBottomHeight){
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
            this->arm->primaryLiftPosition(primaryBottomHeight,   (int)average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));

            this->arm->secondaryLiftPosition(SECONDARY_BOT, this->analog->get_potentiometerVal());
            if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) <= primaryBottomHeight && this->analog->get_potentiometerVal() < SECONDARY_BOT){

              unsigned long intakeTimer = millis();
              robotState = INTAKE;
              this->arm->set_primaryLiftPosPID(9.0,0.0,0.0);
              this->arm->haltPrimaryLift();
              this->arm->haltSecondaryLift();
            }
          break;

          case INTAKE:
            //Intake Cone
            // if(this->analog->get_potentiometerVal() > SECONDARY_BOT || average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > 7){
            //   robotState = BOTTOM;
            // }
            // printf("%ld\n", bot.intakeTimer);

            if(this->digital->get_leftLimitSwitch() == 0 || this->digital->get_rightLimitSwitch() == 0 || millis()-intakeTimer > 2000){
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
            if(isAutonomous() == false){
              robotState = RESTABOVE;
            }else{
              robotState = ADJUSTHEIGHT;
              this->stackedCones++;
            }
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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////CSUN 2 AUTO LOAD CODE////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #define SECONDARY_BOT_CSUN2  3300
// #define SECONDARY_TOP_CSUN2 1700
// #define CONE_HEIGHT_CSUN2 7
// #define MAX_HEIGHT 8
int primaryBottomHeightCSUN2 = 3; //change between 3 and height of loading station at 45

//set to true for loading in the preLoad area. false for picking up cones from the ground
void robot::set_primaryBottomHeightCSUN2(bool toPreLoad){
  if(toPreLoad){
    primaryBottomHeightCSUN2 = 47;
  }
  else{
    primaryBottomHeightCSUN2 = 3;
  }
};

  void robot::autoLoadCSUN2(){
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
                this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
                if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= primaryBottomHeightCSUN2){
                    robotState = BOTTOM;
                    this->ef->set_Power(-100);
                    this->arm->haltPrimaryLift();
                    this->arm->haltSecondaryLift();
                }
              }
              else{
                this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
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
              this->arm->primaryLiftPosition(primaryBottomHeightCSUN2, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));

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
              // if(this->digital->get_leftLimitSwitch() == 0){
                 robotState = CONEHEIGHT;
              //   this->ef->halt();
              // }
            break;
            //this is a change
            case CONEHEIGHT:
              //Raise Primary Lift to correct height (10deg/cone)

              this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));

              this->ef->halt();
              //Raise Secondary Lift to correct height
                if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) >= CONE_HEIGHT*(this->stackedCones-1)){
                    this->arm->secondaryLiftPosition(SECONDARY_TOP_CSUN2, this->analog->get_potentiometerVal());
                }

              if(average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()) > CONE_HEIGHT*(this->stackedCones+1) && this->analog->get_potentiometerVal() > SECONDARY_TOP_CSUN2){
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
              this->arm->primaryLiftPosition(CONE_HEIGHT*(this->stackedCones+1), average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
              if(this->analog->get_potentiometerVal() < SECONDARY_BOT)
              {
                this->arm->haltSecondaryLift();
                this->arm->primaryLiftPosition(primaryBottomHeight + CONE_HEIGHT, average((double)this->digital->leftLiftEncoderVal(),(double)this->digital->rightLiftEncoderVal()));
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
                  this->arm->set_primaryLiftPosPID(9.0,0.0,0.0);
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
