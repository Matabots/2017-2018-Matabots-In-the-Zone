#include "ports.h"
const bool not_reversed = false;
const bool is_reversed = true;
//unsure how to modularize this class due to encoders being
//too specific
class digitalSensors{
  public:
    Encoder leftEncoder;
    Encoder rightEncoder;
    Encoder liftEncoder;
    digitalSensors(){

    };
    void setLiftEncoder(int port1, int port2, bool direction){
      liftEncoder = encoderInit(port1, port2, direction);
    }
    void setLeftEncoder(int port1, int port2, bool direction){
      leftEncoder = encoderInit(port1, port2, direction);
    }
    void setRightEncoder(int port1, int port2, bool direction){
      rightEncoder = encoderInit(port1, port2, direction);
    }
    void resetDriveEncoders(){
      encoderReset(leftEncoder);
      encoderReset(rightEncoder);
    };

    void printEncoderValues(){
      printf("%d\n", encoderGet(leftEncoder));
      printf("%d\n", encoderGet(rightEncoder));
    };
};
