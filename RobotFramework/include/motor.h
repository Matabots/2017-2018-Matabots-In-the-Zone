#ifndef MOTOR_H
#define MOTOR_H
#include "API.h"
#include "PID.h"
#include "units.h"
//#include "motionProfile.h"

class motor{
private:

  int port;
  int power;
  bool reversed;
  bool imeReversed;
  motorType type;
  unsigned char address;
  int count;
  int targetCount;
  int velocity;
  int targetVel;
  int freeRPM;
  int prevTime; //previous millisecond value
  int prevCount;
  int sampleTime; //time it takes between reading values in seconds
  pid* velPID;
  pid* posPID;

public:

  motor(){
    this->power = 0;
    this->reversed = false;
    this->imeReversed = false;
    this->type = TORQUE;
    this->targetVel = 0;
    this->prevTime = millis();
    this->prevCount = 0;
    this->velPID = new pid();
    this->posPID = new pid();
    set_freeRPM();
  };
  motor(int motorPort, double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
    this->imeReversed = false;
    this->type = TORQUE;
    set_freeRPM();
    this->targetVel = 0;
    this->prevTime = millis();
    this->prevCount = 0;
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
    this->posPID = new pid(kPInput,kIInput,kDInput,kFInput);
  };
  motor(int motorPort, unsigned char encoderAddress, double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->address = encoderAddress;
    this->port = motorPort;
    this->power = 0;
    this->targetVel =0;
    this->reversed = false;
    this->imeReversed = false;
    this->prevCount = 0;
    this->type = TORQUE;
  //  set_freeRPM();
    this->prevTime = millis();
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
    this->posPID = new pid(kPInput,kIInput,kDInput,kFInput);
  };

  void set_targetVelocity(int vel){
    if(vel >= this->freeRPM){
      (this->targetVel) = this->freeRPM;
    }
    else{
      (this->targetVel) = vel;
    }
  }
  int get_targetVelocity(){
    return this->targetVel;
  }
  int get_velocity(){
    if(imeGetVelocity(this->address,&this->velocity)){
      this->velocity = imeVelocity((this->velocity), this->type);
      return (this->velocity);
    }else{
      printf("Unable to retrive velocity of encoder");
      return -1;
    };
  };  //control the motor to spin at a certain veloctiy

  int get_targetCount(){
    return targetCount;
  }
  void set_targetCount(int tCount){
    this->targetCount = tCount;
  }

  int get_velocity(Encoder* encoderValue){
    double delta_ms;
    double delta_enc;
    double motor_velocity;
    double ticks_per_rev; //encoder
      ticks_per_rev = 360;
      // Get current encoder value
      // how many mS since we were last here
      double mil = millis();
      delta_ms = (mil-(prevTime));
      this->prevTime = (mil);
      // Change in encoder count
      delta_enc = encoderGet(*encoderValue) - (this->prevCount);
      // save last position
      this->prevCount = encoderGet(*encoderValue);
      //lcdPrint(uart1, 1, "dX:%d DX:%d dT:%d",this->prevCount, encoderValue, this->prevTime);
      // Calculate velocity in rpm
      motor_velocity = ((1000.0*60 )/delta_ms)*(delta_enc/ticks_per_rev);
      // multiply by any gear ratio's being used
      this->velocity =  (int)(motor_velocity/2);
      return (this->velocity);
  };
  void set_velPID(double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
  }
  void set_velPID(pid* controller){
    this->velPID = controller;
  }
  pid* get_velPID(){
    return this->velPID;
  }
  void set_posPID(pid* controller){
    this->posPID = controller;
  }
  pid* get_posPID(){
    return this->posPID;
  }
  void set_freeRPM(){
    this->freeRPM = 100; //Torque: free spin [rpm]
    if(this->type == HIGHSPEED){
      this->freeRPM = 160;
    }
    if(this->type == TURBO){
      this->freeRPM = 240;
    }
  };
  int get_freeRPM(){
    return this->freeRPM;
  }
  motorType get_motorType(){
    return this->type;
  }
  void set_motorType(motorType mType){
    this->type = mType;
  }
  unsigned char get_address(){
    return this->address;
  };
  void set_address(unsigned char add){
    this->address = add;
  }
  bool get_imeReversed(){
    return this->imeReversed;
  };
  void set_imeReversed(bool val){
    this->imeReversed = true;
  };

  int get_count(){
    if(!(this->imeReversed)){
      if(imeGet(this->address, &this->count)){
        return (this->count);
      }
    }
    else if(this->imeReversed){
      if(imeGet(this->address, &this->count)){
        return (-this->count);
      }
    }
      printf("Unable to retrive value of encoder");
      return -1;

  };

  int get_prevCount(){
      return this->prevCount;
  };

  int get_prevTime(){
    return this->prevTime;
  };

  void reset_encoder(){
    imeReset(this->address);
  };
  void set_encoderPort(int encoderPort){
    this->address = encoderPort;
  };
  unsigned char get_encoderPort(){
    return this->address;
  };

  void set_Port(int motorPort){
    this->port = motorPort;
  };
  int get_Port(){
    return this->port;
  }
  void set_Power(int motorPower){
    this->power = motorPower;
    if(this->reversed == false){
      motorSet(this->port, this->power);
    }else{
      motorSet(this->port, (this->power * -1));
    }
  };
  int get_Power(){
    return this->power;
  };
  void set_Direction(bool motorReversed){
    this->reversed = motorReversed;
  };
  bool get_Direction(){
    return this->reversed;
  };
  int get_Speed(){
    return motorGet(this->port);
  };
  void set_type(motorType motor){
    this->type = motor;
  };

  void velocityControlIME(int setPoint){
    // int dt = millis()-prevTime;
    // dt = dt/1000;
    // this->prevTime = millis();
    //set_Power(50);
    double dt = 50;
    set_targetVelocity(setPoint);
    this->velPID->set_setPoint(this->targetVel);
    this->velocity = get_velocity();
    double vel_output = this->velocity+(this->velPID->calculateOutput(this->velocity,dt));
    //calculate velocity based on
    if(abs(this->velPID->get_setPoint()-(this->velocity))>(this->velPID->get_deadband())){
      set_Power(vel_output);
      printf("PID: %f \n",this->velPID->get_kP());
      printf("trg: %d \n", setPoint);
    }
  };

  void velocityControl(Encoder* enc, int setPoint){
    // int mil = millis();
    // double dt = mil-this->prevTime;
    // this->prevTime = mil;
    double dt = 50;
    set_targetVelocity(setPoint);
    this->velPID->set_setPoint(this->targetVel);
    //lcdPrint(uart1, 2, "tV: %f", (double)this->velPID->get_setPoint());
    this->velocity = get_velocity(enc);
    double vel_output = this->velocity+(this->velPID->calculateOutput(this->velocity,dt));//*(this->freeRPM); //the speed of the robot
    //calculate velocity based on
    if(abs(this->velPID->get_setPoint()-(this->velocity)) > (this->velPID->get_deadband())){
      set_Power(vel_output);
    }
  };
  //control the motor to spin to a target degree
  void positionControlIME(double setPointIn){
    double dt = 50;

    this->posPID->set_setPoint(setPointIn);
    this->count = get_count();
    double in = ticksToRotations(this->count,this->type)*(3.14*4);
    printf("in: %f\n",in);
    printf("trgtIn: %f\n",setPointIn);
    printf("dead: %f",this->posPID->get_deadband());
    // // printf("PID: %f \n",this->posPID->get_kP());
    // // printf("trg: %f \n", setPointDeg);
    double vel_output = this->posPID->calculateOutput(in, dt);
    vel_output = vel_output < 25 && vel_output > 0? 25 : vel_output;
    vel_output = vel_output > -25 && vel_output < 0 ? -25 : vel_output;
    if(abs(setPointIn-in) > (this->posPID->get_deadband())){
      set_Power(vel_output); //replace with velocity control when you get chance
      //printf("vel: %f",vel_output);
    //  printf("vel: %f \n",vel_output);
    }
    else{
      set_Power(0);
    }
  };

  //control the motor to spin to a target degree
  void tickControl(double setPointDeg, double currTick){
    double dt = 50;
    double rotations = setPointDeg/360;
    int setPointCount = rotationsToTicks(rotations, this->type);
    set_targetCount(setPointCount);
    //printf("setPt: %d \n", this->targetCount);
    this->posPID->set_setPoint(this->targetCount);
    this->count = currTick;
    // // printf("PID: %f \n",this->posPID->get_kP());
    // // printf("trg: %f \n", setPointDeg);
    double vel_output = this->posPID->calculateOutput(this->count, dt);
    if(abs(this->posPID->get_setPoint()-(this->count)) > (this->posPID->get_deadband())){
      set_Power(vel_output); //replace with velocity control when you get chance
      //printf("vel: %f",vel_output);
    //  printf("vel: %f \n",vel_output);
    }
  };

  //control the motor to spin to a target degree
  void tickControlIME(double setPointDeg){
    double dt = 50;
    double rotations = setPointDeg/360;
    int setPointCount = rotationsToTicks(rotations, this->type);

    set_targetCount(setPointCount);
    printf("setPt: %d \n", this->targetCount);
    this->posPID->set_setPoint(this->targetCount);
    this->count = get_count();
    // // printf("PID: %f \n",this->posPID->get_kP());
    // // printf("trg: %f \n", setPointDeg);
    double vel_output = this->posPID->calculateOutput(this->count, dt);
    if(abs(this->posPID->get_setPoint()-(this->count)) > (this->posPID->get_deadband())){
      set_Power(vel_output); //replace with velocity control when you get chance
      printf("vel: %f",vel_output);
    //  printf("vel: %f \n",vel_output);
    }
  };
};
#endif
