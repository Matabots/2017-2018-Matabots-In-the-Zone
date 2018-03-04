class driveMotors{
public:
  int port;
  int power;
  bool reversed;
  driveMotors(){
    power = 0;
    reversed = false;
  }
  driveMotors(int motorPort){
    port = motorPort;
    power = 0;
    reversed = false;
  }
  void setPort(int motorPort){
    port = motorPort;
  };
  int getPort(){
    return port;
  }
  void setPower(int motorPower){
    power = motorPower;
    if(reversed == false){
      motorSet(port, power);
    }else{
      motorSet(port, (power * -1));
    }
  };
  void setDirection(bool motorReversed){
    reversed = motorReversed;
  };
  bool getDirection(){
    return reversed;
  };
  int getSpeed(){
    return motorGet(port);
  };
  int getPower(){
      return power;
  };
};
