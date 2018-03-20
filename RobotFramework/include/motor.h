#ifndef MOTOR_H
#define MOTOR_H
#include "API.h"
#include "PID.h"
#include "units.h"
#define SMLIB_I_FREE_393        0.2
#define SMLIB_I_STALL_393       4.8
#define SMLIB_RPM_FREE_393      110
#define SMLIB_R_393             (7.2/SMLIB_I_STALL_393)
#define SMLIB_L_393             0.000650
#define SMLIB_Ke_393            (7.2*(1-SMLIB_I_FREE_393/SMLIB_I_STALL_393)/SMLIB_RPM_FREE_393)
#define SMLIB_I_SAFE393         0.90
class motor{
private:

  int port;
  int power;
  bool reversed;
  motorType type;
  unsigned char address;
  int count;
  int velocity;
  int freeRPM;
  int prevTime; //previous millisecond value
  int prevCount;
  pid* velPID;
  pid* posPID;

public:

  motor(){
    this->power = 0;
    this->reversed = false;
    this->type = TORQUE;
    set_freeRPM();
    this->prevTime = millis();
    this->prevCount = 0;
    this->velPID = new pid();
    this->posPID = new pid();
  };
  motor(int motorPort, double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
    this->type = TORQUE;
    set_freeRPM();
    this->prevTime = millis();
    this->prevCount = 0;
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
    this->posPID = new pid(kPInput,kIInput,kDInput,kFInput);
  };
  motor(int motorPort, unsigned char encoderAddress, double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->address = encoderAddress;
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
    this->prevCount = 0;
    this->type = TORQUE;
    set_freeRPM();
    this->prevTime = millis();
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
    this->posPID = new pid(kPInput,kIInput,kDInput,kFInput);
  };


  void velocityControlIME(int setPoint,int dt){
    velPID->set_setPoint(setPoint);
    double vel = (this->freeRPM)*(velPID->calculateOutput(get_velocity(),dt));
    set_velocity((int)vel);
    //calculate velocity based on
    if(get_velocity() < velPID->get_setPoint()){
      this->power = (this->power)+1; //increase the power if it's too weak
    }
    if(get_velocity() > velPID->get_setPoint()){
      this->power = (this->power)-1; //increase the power if it's too weak
    }
  };

  //control the motor to spin to a position
  void positionControl(){
    //float pError = this->
  }

  void set_velocity(int velocity){
    if(this->get_velocity() > this->freeRPM){
      (this->velocity) = this->freeRPM;
    }
    else{
      (this->velocity) = velocity;
    }
  }
  int get_velocity(){
    if(imeGetVelocity(this->address, &this->velocity)){
      set_velocity(imeVelocity((this->velocity), this->type));
      return (this->velocity);
    }else{
      printf("Unable to retrive velocity of encoder");
      return -1;
    };
  };  //control the motor to spin at a certain veloctiy
  double delta_ms;
  double delta_enc;
  int motor_velocity;
  int ticks_per_rev; //encoder

  int get_velocity(int encoderValue){
      ticks_per_rev = 360;
      // Get current encoder value
      // how many mS since we were last here
      delta_ms = (int)(millis()-(prevTime));
      this->prevTime = (int)(millis());
      // Change in encoder count
      delta_enc = encoderValue - (prevCount);
      // save last position
      this->prevCount = encoderValue;
      //lcdPrint(uart1, 1, "dX:%d DX:%d dT:%d",this->prevCount, encoderValue, this->prevTime);
      // Calculate velocity in rpm
      motor_velocity = ((1000.0*60 )/delta_ms)*(delta_enc/ticks_per_rev);
      // multiply by any gear ratio's being used
      this->velocity =  motor_velocity/2;
      return (this->velocity);
  };
  void set_velPID(double kPInput=0, double kIInput=0, double kDInput=0, double kFInput=0){
    this->velPID = new pid(kPInput,kIInput,kDInput,kFInput);
  }
  void set_velPID(pid* controller){
    this->velPID = controller;
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
  int get_motorType(){
    return this->type;
  }
  void set_motorType(motorType mType){
    this->type = mType;
  }
  unsigned char get_address(){
    return this->address;
  };
  void set_count(int inputCount){
    (this->count) = inputCount;
  };
  int get_count(){
    if(imeGet(this->address, &this->count)){
      return (this->count);
    }else{
      printf("Unable to retrive value of encoder");
      return -1;
    };
  };
  int get_prevCount(){
      return this->prevCount;
  };
  int get_prevTime(){
    return this->prevTime;
  }
  void reset_encoder(){
    imeReset(this->address);
  }

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
};
#endif
