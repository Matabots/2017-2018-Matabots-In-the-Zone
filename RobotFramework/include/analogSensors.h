#ifndef ANALOGSENSORS_H
#define ANALOGSENSORS_H

#include "potentiometer.h"
#include "lineSensor.h"
#include "ports.h"
class analogSensors{
  private:
  //potentiometers defined first
  potentiometer rollerPotentiometer;
  //all other analog sensors here
  lineSensor leftLineSensor;
  lineSensor rightLineSensor;
  Gyro gyro;
  int deltaGyro;
  public:

      analogSensors(){
        deltaGyro = 0;
        this->rollerPotentiometer = potentiometer();
        // this->gyro = gyroInit(analog1, 0);
        // this->rollerPotentiometer.set_Potentiometer(analog2);
      };

      void set_deltaGyro(int num){
        this->deltaGyro = num;
      };
      int get_deltaGyro(){
        return this->deltaGyro;
      };
      void set_gyro(int port, int multiplier){
        this->gyro = gyroInit(port, multiplier);
      };
      Gyro get_gyro(){
        return this->gyro;
      };
      int gyro_val(){
        return gyroGet(this->gyro);
      };
      void reset_gyro(){
        gyroReset(this->gyro);
      };
      void set_potentiometer(int port){
        this->rollerPotentiometer.set_Potentiometer(port);
      };
      potentiometer get_potentiometer(){
        return this->rollerPotentiometer;
      };
      int get_potentiometerVal(){
        return this->rollerPotentiometer.getValue();
      };
      void set_leftLineSensor(int port){
        this->leftLineSensor.set_lineSensor(port);
      };
      void set_rightLineSensor(int port){
        this->rightLineSensor.set_lineSensor(port);
      }
      lineSensor get_leftLineSensor(){
        return this->leftLineSensor;
      }
      int get_leftLineSensorVal(){
        return this->leftLineSensor.getValue();
      };
      lineSensor get_rightLineSensor(){
        return this->rightLineSensor;
      }
      int get_rightLineSensorVal(){
        return this->rightLineSensor.getValue();
      };


};
#endif
