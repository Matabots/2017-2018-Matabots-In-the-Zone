#include <SPI.h>


uint16_t number = 0;
//uint8_t number2 = 0;
//uint8_t number3 = 0;
//uint8_t number4 = 0;
//uint8_t number5 = 0;
void setup(){
    Serial.begin(19200);
//    Serial.begin(6000000);
    SPI.begin(); 
}

void loop(){
 delay(500);
 SPISettings settingsA(6000000, MSBFIRST, SPI_MODE0);
 SPI.beginTransaction(settingsA);
 digitalWrite(10, LOW);
 number = SPI.transfer(0);
// number2 = SPI.transfer(0);
// number3 = SPI.transfer(0);
// number4 = SPI.transfer(0);
// number5 = SPI.transfer(0);
 digitalWrite(10, HIGH);
 SPI.endTransaction();
 Serial.println(number);
// Serial.println(number2);
// Serial.println(number3);
// Serial.println(number4);
// Serial.println(number5);
 Serial.println();
 Serial.println();
}


