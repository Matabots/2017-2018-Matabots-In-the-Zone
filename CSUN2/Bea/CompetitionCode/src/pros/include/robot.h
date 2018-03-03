#include "digitalSensors.h"
#include "analogSensors.h"
#include "motors.h"
class robot{
  public:
    int first;
    analogSensors analog = analogSensors();
    digitalSensors digital = digitalSensors();
    driveMotors motors = driveMotors();
    robot(){
      first = 9;
    };
    void printFirst(){
      printf("%d\n", first);
    };
};
