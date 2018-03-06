#ifndef DIGITALSENSORS_H
#define DIGITALSENSORS_H

#include "ports.h"
//unsure how to modularize this class due to encoders being
//too specific
class digitalSensors{
private:
  Encoder leftEncoder;
  Encoder rightEncoder;
  Encoder liftEncoder;

  public:
    digitalSensors(){

    };
    void set_LiftEncoder(int port1, int port2, bool direction){
      this->liftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_LiftEncoder(){
      return this->liftEncoder;
    };
    void set_LeftEncoder(int port1, int port2, bool direction){
      this->leftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_LeftEncoder(){
      return this->leftEncoder;
    };
    void set_RightEncoder(int port1, int port2, bool direction){
      this->rightEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_RightEncoder(){
      return this->rightEncoder;
    };
    void resetDriveEncoders(){
      encoderReset(this->leftEncoder);
      encoderReset(this->rightEncoder);
    };

    void printEncoderValues(){
      printf("%d\n", encoderGet(this->leftEncoder));
      printf("%d\n", encoderGet(this->rightEncoder));
    };
};
#endif
