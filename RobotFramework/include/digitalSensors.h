#ifndef DIGITALSENSORS_H
#define DIGITALSENSORS_H

#include "ports.h"
#include "API.h"
//unsure how to modularize this class due to encoders being
//too specific
class digitalSensors{
  private:
    Encoder leftEncoder;
    Encoder rightEncoder;
    Encoder rightLiftEncoder;
    Encoder leftLiftEncoder;
    Encoder coneLiftEncoder;
    int leftLimitSwitchPort;
    int leftLimitSwitch;
    int rightLimitSwitchPort;
    int rightLimitSwitch;

  public:
    digitalSensors(){

    };
    void set_leftLimitSwitch(int port){
      this->leftLimitSwitchPort = (port);
    };
    int get_leftLimitSwitch(){
      this->leftLimitSwitch = digitalRead(this->leftLimitSwitchPort);
      return this->leftLimitSwitch;
    };
    void set_rightLimitSwitch(int port){
      this->rightLimitSwitchPort = (port);
    };
    int get_rightLimitSwitch(){
      this->rightLimitSwitch = digitalRead(this->rightLimitSwitchPort);
      return this->rightLimitSwitch;
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

    void set_leftLiftEncoder(int port1, int port2, bool direction){
      this->leftLiftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_leftLiftEncoder(){
      return this->leftLiftEncoder;
    };
    int leftLiftEncoderVal(){
      return encoderGet(this->leftLiftEncoder);
    };

    void set_rightLiftEncoder(int port1, int port2, bool direction){
      this->rightLiftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_rightLiftEncoder(){
      return this->rightLiftEncoder;
    };
    int rightLiftEncoderVal(){
      return encoderGet(this->rightLiftEncoder)/2; //for some reason the right side is counting 2x as much
    };

    void set_LeftEncoder(int port1, int port2, bool direction){
      this->leftEncoder = encoderInit(port1, port2, direction);
    };
    Encoder get_LeftEncoder(){
      return this->leftEncoder;
    };
    Encoder* get_pLeftEncoder(){
      return &this->leftEncoder;
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
    void resetLiftEncoders(){
      encoderReset(this->rightLiftEncoder);
      encoderReset(this->leftLiftEncoder);
    };

    void printEncoderValues(){
      printf("%d\n", encoderGet(this->leftEncoder));
      printf("%d\n", encoderGet(this->rightEncoder));
    };
};
#endif
