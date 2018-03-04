class robotClaw{
public:
  driveMotors clawMotor = driveMotors();
  bool reversed;
  robotClaw(){

  }
  void setDirection(bool reversed){
    clawMotor.setDirection(reversed);
  };
  void setPort(int port){
    clawMotor.setPort(port);
  };
  void setPower(int power){
    clawMotor.setPower(power);
  };
  void halt(){
    clawMotor.setPower(0);
  };
  bool getDirection(){
    return reversed;
  };
  int getSpeed(){
    return clawMotor.getSpeed();
  };

};
