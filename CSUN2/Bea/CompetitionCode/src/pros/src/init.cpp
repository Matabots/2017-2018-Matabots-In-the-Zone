#include "main.h"
#include "robot.h"
#include "ports.h"
void initializeIO() {
}

void initialize() {
  printf("Initalize()");
  robot bot = robot();
  bot.digital.resetEncoders();
  bot.drive.addLeftMotor(motor2, not_reversed);
  bot.drive.addLeftMotor(motor8, is_reversed);
  bot.drive.addRightMotor(motor3, not_reversed);
  bot.drive.addRightMotor(motor9, is_reversed);

  //THIS NEEDS TO BE RESET
  setTeamName("3796B");
  imeInitializeAll();
}
