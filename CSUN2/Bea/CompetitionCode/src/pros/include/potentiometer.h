class potentiometer{
public:
  int value;
  int potentiometerPort;

  potentiometer(){

  }
  void setPotentiometer(int port){
    potentiometerPort = port;
  }
  void updateValues(){
    value = analogRead(potentiometerPort);
  }
  int getValue(){
    return analogRead(potentiometerPort);
  }
};
