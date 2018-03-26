/**
 * @file: units.h
 * @created Febuary 8, 2017
 * @author Brendan McGuire
 *
 *  Contains abstractions for units
 */

 #ifndef INCLUDE_UNITS_H_
 #define INCLUDE_UNITS_H_

 #include <API.h>

 typedef enum motorType {
   TORQUE,
   HIGHSPEED,
   TURBO
 } motorType;

#define PI 3.141492653

int imeVelocity(int velocity, motorType motor){
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

double ticksToRotations(Encoder enc){
    return encoderGet(enc)/360;
};

/**
 * Convert ticks to rotations
 * @method ticksToRotations
 * @param  ticks           Ticks
 * @param  motor           The motor type
 * @return                 Rotations
 */
 double ticksToRotations(int ticks, motorType motor){
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

/**
 * Converts rotations to ticks
 * @method rotationsToTicks
 * @param  rotations        Rotations
 * @param  motor            Motor Type
 * @return                  Ticks
 */
 int rotationsToTicks(double rotations, motorType motor){
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
     return 360;
   }
 };

 int rotationsToTicks(Encoder enc){
   return encoderGet(enc)*360;
 }

/**
 * Convert ticks to inches
 * @method ticksToInches
 * @param  ticks         Ticks
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Inches
 */
 double ticksToInches(int ticks, double wheelDiameter, motorType motor) {
     return (ticksToRotations(ticks, motor) * wheelDiameter*PI);
 };
 double ticksToInches(Encoder enc, double wheelDiameter) {
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

  int inchesToTicks(double ticks, double wheelDiameter, motorType motor) {
      return rotationsToTicks(ticks, motor) * wheelDiameter * PI;
  };

#endif /* INCLUDE_XDRIVE_H_ */
