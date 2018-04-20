#include "lineSensor.h"

lineSensor::lineSensor(){

}

void lineSensor::set_lineSensor(int port)
{
  this->lineSensorPort = port;
}
int lineSensor::get_lineSensor()
{
  return this->lineSensorPort;
}
void lineSensor::updateValues()
{
  this->value = analogRead(this->lineSensorPort);
}
int lineSensor::getValue()
{
  return analogRead(this->lineSensorPort);
}
