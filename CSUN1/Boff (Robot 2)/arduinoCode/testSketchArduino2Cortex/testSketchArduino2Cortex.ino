

#include <Wire.h>

int num = 0;

void setup() {
  Wire.begin(1);                // join i2c bus with address #8
  Serial.begin(9600);
  Wire.onReceive(recieveData); // register event
}

void loop() {
  delay(100);
  if(num == 0){
    wire.beginTransmission(2);
    wire.write(1);
    wire.endTransmission();
    num=0;    
  }
}

void recieveData(){
  num = Wire.read(); 
}
