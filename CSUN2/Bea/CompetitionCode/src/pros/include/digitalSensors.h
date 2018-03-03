#include "ports.h"
const bool not_reversed = false;
const bool is_reversed = true;

class digitalSensors{
  public:
    Encoder leftEncoder;
    Encoder rightEncoder;
    digitalSensors(){
      leftEncoder = encoderInit(digital1, digital2, not_reversed);
      rightEncoder = encoderInit(digital3, digital4, not_reversed);
    };

    void resetEncoders(){
      encoderReset(leftEncoder);
      encoderReset(rightEncoder);
    };

    void printEncoderValues(){
      printf("%d\n", encoderGet(leftEncoder));
      printf("%d\n", encoderGet(rightEncoder));
    };
};
