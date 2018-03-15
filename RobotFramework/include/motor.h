#ifndef MOTOR_H
#define MOTOR_H
#include <API.h>

class motor{
private:
  int port;
  int power;
  bool reversed;
  unsigned char address;
  int* count;
  int* velocity;
public:

  motor(){
    this->power = 0;
    this->reversed = false;
  };
  motor(int motorPort){
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
  };
  motor(int motorPort, unsigned char encoderAddress){
    this->address = encoderAddress;
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
  };
  void set_count(int inputCount){
    *(this->count) = inputCount;
  }
  int get_count(){
    if(imeGet(this->address, this->count)){
      return *(this->count);
    }else{
      printf("Unable to retrive value of encoder");
      return -1;
    };
  };
  void set_velocity(int velocity){
    //unifinished. This will increase power until it reaches the target velocity based on velocity input
  }
  int get_velocity(){
    if(imeGetVelocity(this->address, this->velocity)){
      return *(this->velocity);
    }else{
      printf("Unable to retrive velocity of encoder");
      return -1;
    };
  };
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
