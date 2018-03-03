#include "utility/sensors/ime.h"

bool updateIME(IME *ime) {

  ime->lastValue = ime->value;
  return imeGet(ime->address, &ime->value);

}
