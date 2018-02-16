
#include <Wire.h>
int num = 1;
void setup() {
  pinMode(13, OUTPUT);
  Wire.begin(1); // join i2c bus (address optional for master)
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  Wire.beginTransmission(1); // transmit to device #8
  Wire.write(num);              // sends one byte
  Wire.endTransmission();    // stop transmitting
}

void loop() {
  
  if(num==0){
    digitalWrite(13, LOW);
  }
  else{
    digitalWrite(13, HIGH);
    delay(500);
    Wire.beginTransmission(2);
    Wire.write(1);
    Wire.endTransmission();
    num=0;
  }
  delay(100);
}

void receiveEvent(int howMany){
  num = Wire.read();
}

