#include "ports.h"
#include "driveMotors.h"
#include <vector>

class robotChasis{
public:
  std::vector<driveMotors> leftMotors;
  std::vector<driveMotors> rightMotors;

  robotChasis(){

  };

  void addLeftMotor(int port, bool reverse){
    driveMotors leftMotor = driveMotors(port);
    leftMotor.setDirection(reverse);
    leftMotors.push_back(leftMotor);
  };

  void addRightMotor(int port, bool reverse){
    driveMotors rightMotor = driveMotors(port);
    rightMotor.setDirection(reverse);
    rightMotors.push_back(rightMotor);
  }

  void leftPower(int power){
    for(std::vector<driveMotors>::size_type i = 0; i != leftMotors.size(); i++) {
      leftMotors[i].setPower(power);
    }
  };

  void rightPower(int power){
    for(std::vector<driveMotors>::size_type i = 0; i != rightMotors.size(); i++) {
      rightMotors[i].setPower(power);
    }
  };

  void haltLeft(){
    for(std::vector<driveMotors>::size_type i = 0; i != leftMotors.size(); i++) {
      leftMotors[i].setPower(0);
    }
  };

  void haltRight(){
    for(std::vector<driveMotors>::size_type i = 0; i != rightMotors.size(); i++) {
      rightMotors[i].setPower(0);
    }
  };
};
