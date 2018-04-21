#include "autonScripts.h"

void runRedNoPreload(robot bot){
  //bot.driveIn(55);
  printf("this has ended\n");
  bot.setPreloadHeight();
  bot.lowerGoalLift();
  bot.driveIn(47);
  delay(250);
  bot.raiseGoalLift();
  bot.scorePreload();
  delay(250);
  bot.get_drive()->rightPosition(5);
  bot.driveIn(7);
  bot.set_targetStack(2);
  while(bot.get_stackedCones() < bot.get_targetStack()){
    bot.autoLoad();
    delay(50);
  }
  delay(250);
  bot.driveIn(-22);
  bot.set_primaryBottomHeight(true);
  delay(250);
  bot.spinToAngle(107);
  bot.driveIn(-6);
  delay(250);
  bot.set_targetStack(8);
  while(bot.get_stackedCones() < bot.get_targetStack()){
    printf("stacked cones: %d\n", bot.get_stackedCones());
    bot.autoLoad();
    delay(50);
  }

  while(true){
    printf("stacking cones to %d\n",bot.get_targetStack() );
    bot.get_drive()->haltLeft();
    bot.get_drive()->haltRight();
    delay(50);
  }
  // printf("autoload Ran");
   bot.set_primaryBottomHeight(false);
};