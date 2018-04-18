#ifndef AUTONSCRIPTS_H
#define AUTONSCRIPTS_H

#include "robot.h"

void runRedNoPreload(robot bot){
  //bot.driveIn(55);
  printf("this has ended\n");
  bot.lowerGoalLift();
  delay(250);
  bot.driveIn(45);
  delay(250);
  bot.raiseGoalLift();
  delay(250);
  bot.driveIn(-15);
  delay(250);
  bot.spinToAngle(90);
  while(true){
    printf("%d\n",bot.get_analog()->gyro_val());
  }

};



#endif
