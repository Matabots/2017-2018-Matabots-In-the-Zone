/*
 * @file ime.c
 * @created January 26, 2017
 * @author Brendan McGuire
 *
 *  Contains a structure to read IMEs more easily
 */

typedef struct IME {
  // The address of the IME, from 0, the IME plugged into the cortex, up the daisy chain
  char address;

  // Value Storage
  int value;
  int lastValue;

} IME;

/**
 * Update an IME Struct to the current value, and update the last value
 * @method updateIME
 * @param  ime       The IME Struct
 * @return           Whether or not the operation was successful
 */
bool updateIME(IME *ime);
