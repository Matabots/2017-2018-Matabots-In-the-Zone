#ifndef AUTONSCRIPTS_H
#define AUTONSCRIPTS_H

#include "robot.h"

void runRedNoPreload(robot bot){
  //bot.driveIn(55);
  printf("this has ended\n");
  bot.setPreloadHeight();
  bot.lowerGoalLift();
  bot.driveIn(43);
  delay(250);
  bot.raiseGoalLift();
  bot.scorePreload();
  delay(250);
  //bot.spinToAngle(0);
  bot.driveIn(8);
  bot.set_targetStack(2);
  while(bot.get_stackedCones() < bot.get_targetStack()){
    bot.autoLoad();
  }
  delay(250);
  bot.driveIn(-20);
  bot.set_primaryBottomHeight(true);
  delay(250);
  bot.spinToAngle(100);
  bot.driveIn(-3);
  delay(250);
  bot.set_targetStack(3);

  printf("targetStack");
  while(bot.get_stackedCones() < bot.get_targetStack()){
    bot.autoLoad();
  }

  printf("autoload Ran");
  bot.set_primaryBottomHeight(false);
};



#endif
