#include "units.h"

void units::printState(state rState){
  switch(rState){
    case BOTTOM:
      printf("BOTTOM\n");
    break;
    case INTAKE:
      printf("INTAKE\n");
    break;
    case CONEHEIGHT:
      printf("CONEHEIGHT\n");
    break;
    case OUTTAKE:
      printf("OUTTAKE\n");
    break;
    case ADJUSTHEIGHT:
      printf("ADJUSTHEIGHT\n");
    break;

  }
};

double units::avg(double num1, double num2){
  return (num1-num2)/2;
};

double units::getTypeTicks(motorType motor){
  if(motor == TORQUE){
    return 627.2;
  }
  if(motor == HIGHSPEED){
    return 392;
  }
  if(motor == TURBO){
    return 261.333;
  }
  else{
    return 360;
  }
};

int units::imeVelocity(int velocity, motorType motor){
  if(motor == TORQUE){//
    return velocity/39.2;
  }
  if(motor == HIGHSPEED){
    return velocity/24.5;
  }
  if(motor == TURBO){
    return velocity/16.33;
  }
  else{
    return 0;
  }
};

double units::ticksToRotations(Encoder enc){
    return encoderGet(enc)/360;
};

/**
 * Convert ticks to rotations
 * @method ticksToRotations
 * @param  ticks           Ticks
 * @param  motor           The motor type
 * @return                 Rotations
 */
 double units::ticksToRotations(int ticks, motorType motor){
   if(motor == TORQUE){
     return ticks/627.2;
   }
   if(motor == HIGHSPEED){
     return ticks/392;
   }
   if(motor == TURBO){
     return ticks/261.333;
   }
   else{
     return 1/360;
   }
 };

double units::ticksToDegrees(int ticks, motorType motor){
  return ticksToRotations(ticks, motor)/360;
};
/**
 * Converts rotations to ticks
 * @method rotationsToTicks
 * @param  rotations        Rotations
 * @param  motor            Motor Type
 * @return                  Ticks
 */
 int units::rotationsToTicks(double rotations, motorType motor){
   if(motor == TORQUE){//
     return rotations*627.2;
   }
   if(motor == HIGHSPEED){
     return rotations*392;
   }
   if(motor == TURBO){
     return rotations*261.333;
   }
   else{
     return rotations*360;
   }
 };

 int units::rotationsToTicks(Encoder enc){
   return encoderGet(enc)*360;
 };

/**
 * Convert ticks to inches
 * @method ticksToInches
 * @param  ticks         Ticks
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Inches
 */
 double units::ticksToInches(int ticks, double wheelDiameter, motorType motor) {
     return (ticksToRotations(ticks, motor) * wheelDiameter*PI);
 };
 double units::ticksToInches(Encoder enc, double wheelDiameter) {
     return (ticksToRotations(enc) * wheelDiameter*PI);
 };

/**
 * Convert inches to ticks
 * @method inchesToTicks
 * @param  inches        Inches
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Ticks
 */

  double units::inchesToDeg(double inches, double wheelDiameter, motorType motor) {
      return (360*inches)/(wheelDiameter * PI);
  };
  double units::degToInches(double deg, double wheelDiameter){
    return (wheelDiameter*PI*deg)/360;
  };
