#include "potentiometer.h"
  potentiometer::potentiometer(){

  };

  void potentiometer::set_Potentiometer(int port){
    this->potentiometerPort = port;
  };
  int potentiometer::get_Potentiometer(){
    return this->potentiometerPort;
  };
  void potentiometer::updateValues(){
    this->value = analogRead(this->potentiometerPort);
  }
  int potentiometer::getValue(){
    return analogRead(this->potentiometerPort);
  }
