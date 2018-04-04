#ifndef PID_H
#define PID_H

#include "API.h"
#include "math.h"
#include <limits>
class pid{
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
    double toleranceI;
    int sampleTime; //time it takes between reading values in seconds
    bool continuous;  //if it is absolute (wraps around). If true, the PID controller considers the max and min as the same value.

  public:
    pid(){
      this->kP = 0;
      this->kI = 0;
      this->kD = 0;
      this->kF = 0;
      this->setPoint = 0.0;

      this->maxInput = std::numeric_limits<int>::max();//120.0;
      this->minInput = std::numeric_limits<int>::min();//-100.0;

      this->maxOutput = 100.0;
      this->minOutput = -120.0;
      this->error = 0.0;
      this->prevError = 0.0;
      this->totalError = 0.0;
      this->output = 0.0;
      this->deadband = 3;
      this->toleranceI = 15;
      this->sampleTime = pow(10,-2); //seconds
      this->continuous = false;
    };
    pid(double kPInput, double kIInput, double kDInput, double kFInput){
      this->kP = kPInput;
      this->kI = kIInput;
      this->kD = kDInput;
      this->kF = kFInput;
      this->sampleTime = 10;
      this->setPoint = 0;

      this->maxInput = std::numeric_limits<int>::max();// 100.0;
      this->minInput = std::numeric_limits<int>::min();// -100.0;

      this->maxOutput = 120.0;
      this->minOutput = -120.0;
      this->error = 0.0;
      this->prevError = 0.0;
      this->totalError = 0.0;
      this->output = 0.0;
      this->deadband = 3;
      this->toleranceI = 15;
      this->continuous = false;
    };

    double calculateOutput(double input, double dt){ //dt is in milliseconds
      dt = dt/1000;
      if(dt < (pow(10,-6))){
        dt = pow(10,-6);
      }

      this->error = (this->setPoint) - input;

      if(continuous == true){
        if(abs(this->error) > ((this->maxInput)-(this->minInput))/2){
          if(this->error > 0){
            this->error = (this->error)-(this->maxInput)+(this->minInput);
          }
          else{
            this->error = (this->error)+(this->maxInput)-(this->minInput);
          }
        }
      }

      //if((this->error)*(this->kP) < this->maxOutput && (this->error)*(this->kP) > this->minOutput){
      if(abs((this->error)) < abs(this->toleranceI)){
        this->totalError += (this->error)*dt;
      } else{
        this->totalError = 0;
      }

      double pError = abs(this->error)<abs(this->deadband) ? 0 : (this->error);
      double dError = ((this->error)-((this->prevError))/(dt));
      this->output = ((this->kP)*pError) + ((this->kI)*(this->totalError)) + ((this->kD)*(dError) + (this->kF)*(this->setPoint));


      this->prevError = this->error;
      this->prevInput = input;

      if((this->output)>(this->maxOutput)){
        this->output = this->maxOutput;
      }
      if((this->output)<(this->minOutput)){
        this->output = this->minOutput;
      }
      //lcdPrint(uart1, 2, "out: %f", this->output);
      lcdPrint(uart1,2,"kP: %f",this->kP);
      return this->output;
    };
    void set_kP(double kPInput){
      this->kP = kPInput;
    };
    double get_kP(){
      return this->kP;
    };
    void set_kI(double kIInput){
      this->kI = kIInput;
    };
    double get_kI(){
      return this->kI;
    };
    void set_kD(double kDInput){
      this->kD = kDInput;
    };
    double get_kD(){
      return this->kD;
    };
    double get_output(){
      return this->output;
    };
    double get_error(){
      return this->error;
    };
    double get_prevError(){
      return this->prevError;
    };
    double get_totalError(){
      return this->totalError;
    };
    void set_sampleTime(int inputSampleTime){
      this->sampleTime = inputSampleTime;
    };
    int get_sampleTime(){
      return this->sampleTime;
    };
    void set_setPoint(int target){
      if((this->maxInput)>(this->minInput)){
        if(target > this->maxInput){
          this->setPoint = this->maxInput;
        }
        else if(target < this->minInput){
          this->setPoint = this->minInput;
        }
        else{
          this->setPoint = target;
        }
      }
    };
    int get_setPoint(){
      return this->setPoint;
    };
    void set_MinMaxOutput(double min, double max){
      if(min > max){
        printf("LOWER BOUNDARY IS GREATER THAN UPPER BOUND\n");
      }
      this->maxOutput = max;
      this->minOutput = min;
    };
    void set_MinMaxInput(double min, double max){
      if(min > max){
        printf("LOWER BOUNDARY IS GREATER THAN UPPER BOUND\n");
      }
      this->maxInput = max;
      this->minInput = min;
      set_setPoint(this->setPoint);
    };
    void set_deadband(int band){
      this->deadband = band;
    };
    double get_deadband(){
      return this->deadband;
    };
    void set_toleranceI(double tolerance){
      this->toleranceI = tolerance;
    };
    double get_toleranceI(){
      return this->toleranceI;
    }
    void set_prevInput(double input){
      this->prevInput = input;
    };
    double get_prevInput(){
      return this->prevInput;
    };
    void set_maxMinInput(int max,int min){
      this->maxInput = max;
      this->minInput = min;
    }
    void set_continuous(bool val){
      this->continuous = val;
    };
    bool isContinuous(){
      return this->continuous;
    };
};
#endif
