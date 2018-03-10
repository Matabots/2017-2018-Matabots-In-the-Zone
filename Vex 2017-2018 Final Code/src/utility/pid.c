/*
 * @file pid.c
 * @created March 2, 2017
 * @author Brendan McGuire
 * @brief Basic PID for PROS. This is built upon by PID Strategies, which provide PID Solutions to specific problems
 */

#include "pid/pid.h"



void resetPID(PIDConfiguration *pid) {
  pid->totalError = 0;
  pid->lastError = 0;
};


int computePID(PIDConfiguration *pid, int target, int sensor) {

  int error = target - sensor;


};
