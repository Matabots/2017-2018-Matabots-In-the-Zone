#ifndef CHASSIS_H
#define CHASSIS_H

#include "ports.h"
#include "motor.h"
#include "math.h"
#include <vector>
#include "path.h"
#include "analogSensors.h"
#define vSAMPLE_PERIOD 100  //Sample period for digital control
class chassis{
private:
  std::vector<motor*> leftMotors;
  std::vector<motor*> rightMotors;
  int wheelDiameter;
  float gearRatio;
  pid* chassisVelPID;
  pid* chassisPosPID;
  pid* chassisGyroPID;
  path* waypoints;
  CartesianVector currPos;
public:

  chassis();

  void updatePos();
  void generatePathTo(CartesianVector targetPos);
  std::vector<motor*> get_leftMotors();
  void set_leftMotors(std::vector<motor*> motors);
  std::vector<motor*> get_rightMotors();
  void set_rightMotors(std::vector<motor*> motors);
  motor* getLeftMotorAt(int pos);
  motor* getRightMotorAt(int pos);
  CartesianVector get_currPos();
  void set_currPos(double x, double y);
  void addLeftMotor(int port, bool reverse);

  void addRightMotor(int port, bool reverse);

  void leftPower(int power);

  void rightPower(int power);

  void leftVelocity(Encoder* enc, int vel);

  void rightVelocity(Encoder* enc, int vel);

  void leftVelocity(int vel);

  void rightVelocity(int vel);

  //
  void leftPosition(int posInch);

  void rightPosition(int posInch);

  void haltLeft();

  void haltRight();

  bool atPos = false;
  void moveDistance(float inch);


  void moveToPos(CartesianVector vector);

  bool atGyro = false;
  void spinToAngle(int targetAngle, analogSensors* gyro);

  void turnRightToAngle(int targetAngle, analogSensors* gyro);
  void turnLeftToAngle(int targetAngle, analogSensors* gyro);

  //unfinished, robot gives inconsistent values
  void driveToLine(int power, analogSensors* leftLine, analogSensors* rightLine);
  int get_wheelDiameter();

  void set_wheelDiameter(int dia);

  path* get_waypoints();
};
#endif
