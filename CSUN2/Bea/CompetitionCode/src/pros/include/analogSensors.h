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
        gyro = gyroInit(analog1, 0);
        clawPotentiometer.setPotentiometer(analog2);
      };
      void set_gyro(int one, int two){
        gyro = gyroInit(one, two);
      };
      void set_potentiometer(int port){
        clawPotentiometer.setPotentiometer(port);
      };
};
