#include "utility/units.h"

double ticksToInches(int ticks, double wheelDiameter, motorType motor) {
    return ticksToRotations(ticks, motor) / wheelDiameter / PI;
}

int inchesToTicks(double ticks, double wheelDiameter, motorType motor) {
    return rotationsToTicks(ticks, motor) * wheelDiameter * PI;
}
