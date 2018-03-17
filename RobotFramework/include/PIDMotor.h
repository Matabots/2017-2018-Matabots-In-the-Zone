#include "motor.h"

#define TOLERANCE 0.5

class PIDMotor : public motor
{
  private:
    double kP;
    double kI;
    double kD;
    double kF;  //feed forward term
    double setPoint; //setPoint value
    double maxOutput;
    double minOutput;
    double maxInput;
    double minInput;
    double prevInput;
    double error;
    double prevError;
    double totalError;
    double output;
    double deadband;  //the time in which the PID controller maintains output. If the error is less than deadband, treat error for kP as 0
    int sampleTime; //time it takes between reading values in seconds
    bool continuous;  //if it is absolute (wraps around). If true, the PID controller considers the max and min as the same value.

  public:
    PIDMotor():motor(){
      this->kP = 0;
      this->kI = 0;
      this->kD = 0;
      this->kF = 0;
      this->setPoint = 0.0;
      this->maxInput = 1.0;
      this->minInput = -1.0;
      this->error = 0.0;
      this->prevError = 0.0;
      this->totalError = 0.0;
      this->output = 0.0;
      this->deadband = 0.0;
      this->sampleTime = 10*(10^-3); //seconds
      this->continuous = true;
    }
    PIDMotor(int motorPort, unsigned char encoderAddress, double kPInput, double kIInput, double kDInput, int inputSampleTime):motor(motorPort,encoderAddress){
      this->kP = kPInput;
      this->kI = kIInput;
      this->kD = kDInput;
      this->sampleTime = inputSampleTime;
      this->setPoint = 0;
      this->maxInput = 1.0;
      this->minInput = -1.0;
      this->error = 0.0;
      this->prevError = 0.0;
      this->totalError = 0.0;
      this->output = 0.0;
      this->deadband = 0.0;
      this->continuous = false;
    }

    void getSample(){
      if((int)millis()<this->sampleTime){
        this->set_count(imeGet(get_address(), get_pCount()));
      }
      if((int)millis()<(this->sampleTime)/2){
        this->set_count(imeGet(get_address(),get_pCount()));
      }
    }

    double calculateOutput(double input, double dt){
      if(dt < (10^-6)){
        dt = 10^-6;
      }
      this->prevInput = input;
      this->error = (this->setPoint) - input;
      if(continuous){
        if(abs(this->error) > ((this->maxInput)-(this->minInput))/2){
          if(this->error > 0){
            this->error = (this->error)-(this->maxInput)+(this->minInput);
          }
          else{
            this->error = (this->error)+(this->maxInput)-(this->minInput);
          }
        }
      }

      if((this->error)*(this->kP) < this->maxOutput && (this->error)*(this->kP) > this->minOutput){
        this->totalError += (this->error)*dt;
      } else{
        this->totalError = 0;
      }

      double pError = abs(this->error)<(this->deadband) ? 0 : (this->error);
      double dError = ((this->error)-(this->prevError))/(this->sampleTime);
      this->output = ((this->kP)*pError) + ((this->kI)*(this->totalError)) + ((this->kD)*(dError));
      this->prevError = this->error;

      if((this->output)>(this->maxOutput)){
        this->output = this->maxOutput;
      }
      if((this->output)<(this->minOutput)){
        this->output = this->minOutput;
      }
      return this->output;
    }

    void velocityControl(){
      float vError = (this->setPoint)-get_velocity();
      if(abs(vError) < TOLERANCE){
        //reached setPoint velocity
      }
    }

    void positionControl(){
      //float pError = this->
    }

    void set_kP(double kPInput){
      this->kP = kPInput;
    }
    float get_kP(){
      return this->kP;
    }
    void set_kI(double kIInput){
      this->kI = kIInput;
    }
    float get_kI(){
      return this->kI;
    }
    void set_kD(double kDInput){
      this->kD = kDInput;
    }
    float get_kD(){
      return this->kD;
    }
    double get_output(){
      return this->output;
    }
    double get_error(){
      return this->error;
    }
    double get_prevError(){
      return this->prevError;
    }
    double get_totalError(){
      return this->totalError;
    }
    void set_sampleTime(int inputSampleTime){
      this->sampleTime = inputSampleTime;
    }
    int get_sampleTime(){
      return this->sampleTime;
    }
    void set_setPoint(int target){
      if((this->maxInput)>(this->minInput)){
        if(target > maxInput){
          this->setPoint = maxInput;
        }
        else if(target < minInput){
          this->setPoint = minInput;
        }
        else{
          this->setPoint = target;
        }
      }
    }
    int get_setPoint(){
      return this->setPoint;
    }
    void set_MinMaxOutput(double min, double max){
      if(min > max){
        printf("LOWER BOUNDARY IS GREATER THAN UPPER BOUND\n");
      }
      this->maxOutput = max;
      this->minOutput = min;
    }
    void set_MinMaxInput(double min, double max){
      if(min > max){
        printf("LOWER BOUNDARY IS GREATER THAN UPPER BOUND\n");
      }
      this->maxInput = max;
      this->minInput = min;
      set_setPoint(this->setPoint);
    }
    void set_deadband(int band){
      this->deadband = deadband;
    }
    double get_deadband(){
      return this->deadband;
    }
    void set_prevInput(double input){
      this->prevInput = input;
    }
    double get_prevInput(){
      return this->prevInput;
    }
    void set_continuous(bool val){
      this->continuous = val;
    }
    bool isContinuous(){
      return this->continuous;
    }
};
