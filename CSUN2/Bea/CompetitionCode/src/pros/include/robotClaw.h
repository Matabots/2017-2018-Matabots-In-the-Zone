class robotClaw{
private:
  driveMotors clawMotor;
  bool reversed;

public:

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
  void set_clawMotor(){
     clawMotor = driveMotors();
  };
  void set_direction(){
     clawMotor = driveMotors();
  };
};
