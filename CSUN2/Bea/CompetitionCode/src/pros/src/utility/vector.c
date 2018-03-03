/*
 * @file: vector.h
 * @created Febuary 2, 2017
 * @author Brendan McGuire
 *
 * This implements all sorts of functions related to vectors, as well as defines Polar and Cartesian Vectors
 */

#include "main.h"

CartesianVector PolarToCartesian(PolarVector vector) {
  CartesianVector output;

  output.x = vector.r * cos(vector.angle);
  output.y = vector.r * sin(vector.angle);

  return output;
}

PolarVector CartesianToPolar(CartesianVector vector) {
  PolarVector output;

  output.r = sqrt(
    (vector.x * vector.x) + (vector.y * vector.y)
  );
  output.angle = atan(vector.y / vector.x);

  return output;
}
