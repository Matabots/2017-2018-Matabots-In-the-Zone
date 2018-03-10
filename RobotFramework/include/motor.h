#ifndef MOTOR_H
#define MOTOR_H

class motor{
private:
  int port;
  int power;
  bool reversed;
public:
  motor(){
    this->power = 0;
    this->reversed = false;
  }
  motor(int motorPort){
    this->port = motorPort;
    this->power = 0;
    this->reversed = false;
  }
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
    reversed = motorReversed;
  };
  bool get_Direction(){
    return reversed;
  };
  int get_Speed(){
    return motorGet(this->port);
  };
};
#endif
