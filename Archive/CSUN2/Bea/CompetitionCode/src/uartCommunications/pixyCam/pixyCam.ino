#include <SPI.h>
#include <Pixy.h>
#include <SoftwareSerial.h>
Pixy pixy;

SoftwareSerial gtSerial(1, 0); // Arduino RX, Arduino TX

void setup()
{
  Serial.begin(115200);
  gtSerial.begin(115200);
  pixy.init();
}

void loop()
{
  static int i = 0;
  int j;
  int coneSize = 0;
  int coneCalc = 0;
  int objectNumber = 0;
  uint16_t blocks;
  String sentence = "";
  blocks = pixy.getBlocks();
  char signatureSelection = 'a';


//  if (gtSerial.available() > 0) {
//    // read the incoming byte:
//
//    signatureSelection = gtSerial.read();
//    // say what you got:
//    //Serial.print("I received: ");
//    //Serial.println(incomingByte, DEC);
//    Serial.println(signatureSelection);
//  }

  delay(100);
  if (blocks > 0)
  {
    objectNumber = 999;
    coneSize = 0;

    for (j = 0; j < blocks; j++)
    {
      coneCalc = (pixy.blocks[j].width * pixy.blocks[j].height);
      if ( (coneCalc > coneSize) && (pixy.blocks[j].signature == 3) && coneCalc > 150) {
        coneSize = coneCalc;
        objectNumber = j;
      }
      else {
        objectNumber = 999;
      }
    }
    if (objectNumber != 999) {
      pixy.blocks[objectNumber].print();
      sentence += "x: ";
      sentence += String(pixy.blocks[objectNumber].x);
      sentence += " y: ";
      sentence += String(pixy.blocks[objectNumber].y);
      sentence += "#";
      gtSerial.print(sentence);
      sentence = "";
    }
    else {
      Serial.println("No object found");
      gtSerial.write("No Object Found#");
    }

  }
}

