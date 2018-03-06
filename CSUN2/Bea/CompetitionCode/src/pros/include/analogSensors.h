#ifndef ANALOGSENSORS_H
#define ANALOGSENSORS_H

#include "potentiometer.h"
#include "ports.h"
class analogSensors{
  private:
  //potentiometers defined first
  potentiometer clawPotentiometer;
  //all other analog sensors here
  Gyro gyro;
  public:

      analogSensors(){
        this->gyro = gyroInit(analog1, 0);
        this->clawPotentiometer = potentiometer();
        this->clawPotentiometer.set_Potentiometer(analog2);
      };
      void set_gyro(int one, int two){
        this->gyro = gyroInit(one, two);
      };
      Gyro get_gyro(){
        return this->gyro;
      };
      void set_potentiometer(int port){
        this->clawPotentiometer.set_Potentiometer(port);
      };
      potentiometer get_potentiometer(){
        return this->clawPotentiometer;
      };

};
#endif
