#ifndef AUTONSCRIPTS_H
#define AUTONSCRIPTS_H

#include "robot.h"

void runRedNoPreload(robot bot){
  //bot.driveIn(55);
  printf("this has ended\n");
  delay(500);
  bot.driveIn(3);
  wait(1000);
  bot.lowerGoalLift();
  wait(1000);
  bot.driveIn(4);
  wait(1000);
  bot.raiseGoalLift();
  wait(1000);
  bot.driveIn(-4);

};



#endif
