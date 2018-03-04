#include "digitalSensors.h"
#include "analogSensors.h"
#include "robotChasis.h"
class robot{
  public:
    analogSensors analog = analogSensors();
    digitalSensors digital = digitalSensors();
    robotChasis drive = robotChasis();
    robot(){
      
    };

};
