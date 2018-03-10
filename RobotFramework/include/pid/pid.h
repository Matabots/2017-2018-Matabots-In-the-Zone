/*
 * @file pid.h
 * @created March 2, 2017
 * @author Brendan McGuire
 * @brief Basic PID Implementation for PROS. This is built upon by PID Strategies, which provide PID Solutions to specific problems
 */


 #ifndef INCLUDE_PID_H_
 #define INCLUDE_PID_H_

typedef struct PIDConfiguration {

  // Control Variables
  double P;
  double I;
  double D;

  // Constraints
  int outputMax = 127;
  int outputMin = 0;

  

  // Tracking Variables
  int totalError;
  int lastError;
};


/**
 * Resets a PID, remove any preexisting error. Use this in between drive actions, etc.
 * @method initalizePID
 * @param  pid          The PID Configuration to reset / initalize
 */
void resetPID(PIDConfiguration *pid);

/**
 * Calculates the output of the PID when given input
 * @method computePID
 * @param  pid        The PID Configuration
 * @param  target     The target you want to reach
 * @param  sensor     The adjusted value from your sensors
 * @return            The output to use
 */
int computePID(PIDConfiguration *pid, int target, int sensor);

#endif /* INCLUDE_PID_H_ */
