#include "motor.h"

class PIDMotor : public motor
{
  private:
    float kP;
    float kI;
    float kD;
    int sampleTime; //time it takes between reading values in milliseconds
    int target; //target value

  public:
    PIDMotor():motor(){
      this->kP = 0;
      this->kI = 0;
      this->kD = 0;
      this->sampleTime = 10;
      this->target = 0;
    }
    PIDMotor(int motorPort, unsigned char encoderAddress, float kPInput, float kIInput, float kDInput, int inputSampleTime):motor(motorPort,encoderAddress){
      this->kP = kPInput;
      this->kI = kIInput;
      this->kD = kDInput;
      this->sampleTime = inputSampleTime;
      this->target = 0;
    }
    void set_kP(float kPInput){
      this->kP = kPInput;
    }
    float get_kP(){
      return this->kP;
    }
    void set_kI(float kIInput){
      this->kI = kIInput;
    }
    float get_kI(){
      return this->kI;
    }
    void set_kD(float kDInput){
      this->kD = kDInput;
    }
    float get_kD(){
      return this->kD;
    }
    void set_sampleTime(int inputSampleTime){
      this->sampleTime = inputSampleTime;
    }
    int get_sampleTime(){
      return this->sampleTime;
    }
    void set_target(int inputTarget){
      this->target = inputTarget;
    }
    int get_target(){
      return this->target;
    }
    void getSample(){
      if((int)millis()<this->sampleTime){
        this->set_count(imeGet(get_address() ,get_pCount()));
      }
    }
};
