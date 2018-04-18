#ifndef LINESENSOR_H
#define LINESENSOR_H

#include "API.h"
class lineSensor{
private:
  int value;
  int lineSensorPort;
public:
  lineSensor(){

  }

  void set_lineSensor(int port)
  {
    this->lineSensorPort = port;
  }
  int get_lineSensor()
  {
    return this->lineSensorPort;
  }
  void updateValues()
  {
    this->value = analogRead(this->lineSensorPort);
  }
  int getValue()
  {
    return analogRead(this->lineSensorPort);
  }

};
#endif
