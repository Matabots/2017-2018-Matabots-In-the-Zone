#include "ports.h"
#include <vector>
class liftMotors{
public:
  std::vector<driveMotors> groupOne;
  std::vector<driveMotors> groupTwo;
  liftMotors(){

  };

  void addGroupOneMotor(int port, bool reverse){
    driveMotors liftMotor = driveMotors(port);
    liftMotor.setDirection(reverse);
    groupOne.push_back(liftMotor);
  };

  void addGroupTwoMotor(int port, bool reverse){
    driveMotors liftMotor = driveMotors(port);
    liftMotor.setDirection(reverse);
    groupTwo.push_back(liftMotor);
  }

  void groupOnePower(int power){
    for(std::vector<driveMotors>::size_type i = 0; i != groupOne.size(); i++) {
      groupOne[i].setPower(power);
    }
  };

  void groupTwoPower(int power){
    for(std::vector<driveMotors>::size_type i = 0; i != groupTwo.size(); i++) {
      groupTwo[i].setPower(power);
    }
  };

  void haltGroupOne(){
    for(std::vector<driveMotors>::size_type i = 0; i != groupOne.size(); i++) {
      groupOne[i].setPower(0);
    }
  };

  void haltGroupTwo(){
    for(std::vector<driveMotors>::size_type i = 0; i != groupTwo.size(); i++) {
      groupTwo[i].setPower(0);
    }
  };
};
