#include "potentiometer.h"
#include "ports.h"
class analogSensors{
  public:
      //potentiometers defined first
      potentiometer clawPotentiometer = potentiometer();
      //all other analog sensors here
      Gyro gyro;
      analogSensors(){
        gyro = gyroInit(analog1, 0);
        clawPotentiometer.setPotentiometer(analog2);
      };
};
