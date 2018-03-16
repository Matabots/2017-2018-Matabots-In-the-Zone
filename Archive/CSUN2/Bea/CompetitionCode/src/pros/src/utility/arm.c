/*
 * @file arm.c
 * @created January 27, 2017
 * @author Brendan McGuire
 * @brief Implementor for arm.h
 */

#include "utility/arm.h"
#include "main.h"
#include "utility/motors.h"

int armSpeedMoveUp = 100;
int armSpeedMoveDown = 40;

int armSpeedFling = 100;

void moveArm(int direction, bool fling) {
  if (direction == -1) {
    direction *= armSpeedMoveDown;
  } else {
    if (fling) {
      direction *= armSpeedFling;
    } else {
      direction *= armSpeedMoveUp;
    }
  }

  moveArmDirect(direction);
}

void moveArmDirect(int power) {
  motorSet(ArmInnerLeft, -power);
  motorSet(ArmInnerRight, power);
  motorSet(ArmOuter, -power);
}

void moveClaw(int power) {
    motorSet(Claw, power);
}
