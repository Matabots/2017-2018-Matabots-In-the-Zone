#include "robot.h"
#include "ports.h"
void setupBot(robot& bot){
  bot.drive.addLeftMotor(motor2, not_reversed);
  bot.drive.addLeftMotor(motor8, is_reversed);
  bot.drive.addRightMotor(motor3, not_reversed);
  bot.drive.addRightMotor(motor9, is_reversed);
}
