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
  Encoder coneLiftEncoder;
  public:
    digitalSensors(){

    };
    void set_coneLiftEncoder(int port1, int port2, bool direction){
      this->coneLiftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_coneLiftEncoder(){
      return this->coneLiftEncoder;
    };
    int coneLiftEncoderVal(){
      return encoderGet(this->coneLiftEncoder);
    };
    void set_LiftEncoder(int port1, int port2, bool direction){
      this->liftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_LiftEncoder(){
      return this->liftEncoder;
    };
    int liftEncoderVal(){
      return encoderGet(this->liftEncoder);
    };
    void set_LeftEncoder(int port1, int port2, bool direction){
      this->leftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_LeftEncoder(){
      return this->leftEncoder;
    };
    int leftEncoderVal(){
      return encoderGet(this->leftEncoder);
    };
    void set_RightEncoder(int port1, int port2, bool direction){
      this->rightEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_RightEncoder(){
      return this->rightEncoder;
    };
    int rightEncoderVal(){
      return encoderGet(this->rightEncoder);
    };
    void resetDriveEncoders(){
      encoderReset(this->leftEncoder);
      encoderReset(this->rightEncoder);
    };
    void resetLiftEncoder(){
      encoderReset(this->liftEncoder);
    };

    void printEncoderValues(){
      printf("%d\n", encoderGet(this->leftEncoder));
      printf("%d\n", encoderGet(this->rightEncoder));
    };
};
#endif
