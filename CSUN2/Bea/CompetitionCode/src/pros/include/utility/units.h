/**
 * @file: units.h
 * @created Febuary 8, 2017
 * @author Brendan McGuire
 *
 *  Contains abstractions for units
 */

 #ifndef INCLUDE_UNITS_H_
 #define INCLUDE_UNITS_H_

typedef enum motorType {
  TORQUE,
  HIGHSPEED,
  TURBO
} motorType;

#define PI 3.141492653

/**
 * Convert ticks to rotations
 * @method ticksToRotations
 * @param  ticks           Ticks
 * @param  motor           The motor type
 * @return                 Rotations
 */
double ticksToRotations(int ticks, motorType motor);

/**
 * Converts rotations to ticks
 * @method rotationsToTicks
 * @param  rotations        Rotations
 * @param  motor            Motor Type
 * @return                  Ticks
 */
int rotationsToTicks(double rotations, motorType motor);

/**
 * Convert ticks to inches
 * @method ticksToInches
 * @param  ticks         Ticks
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Inches
 */
double ticksToInches(int ticks, double wheelDiameter, motorType motor);

/**
 * Convert inches to ticks
 * @method inchesToTicks
 * @param  inches        Inches
 * @param  wheelDiameter The wheel diameter
 * @param  motor         The motor type
 *
 * @return               Ticks
 */
int inchesToTicks(double inches, double wheelDiameter, motorType motor);

#endif /* INCLUDE_XDRIVE_H_ */
