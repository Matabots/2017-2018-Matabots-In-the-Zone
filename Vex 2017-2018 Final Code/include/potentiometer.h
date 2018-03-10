#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class potentiometer{
private:
  int value;
  int potentiometerPort;
public:
  potentiometer(){

  }

  void set_Potentiometer(int port){
    this->potentiometerPort = port;
  }
  int get_Potentiometer(){
    return this->potentiometerPort;
  };
  void updateValues(){
    this->value = analogRead(this->potentiometerPort);
  }
  int getValue(){
    return analogRead(this->potentiometerPort);
  }
};
#endif
