/**
 * @file: utility.c
 * @created 1/26/17
 * @author Brendan McGuire
 *
 * Common utility functions incorporated by multiple utilitys
 */

#include "main.h"

int clamp(int d, int min, int max, int overrideMin, int overrideMax) {
  const int t = abs(d) < min ? overrideMin : d;
  return t > max ? overrideMax : t;
}

int abs(int value) {
  return (value < 0 ? -value : value);
}
