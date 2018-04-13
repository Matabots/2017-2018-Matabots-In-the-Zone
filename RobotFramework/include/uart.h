#ifndef BOTUART_H
#define BOTUART_H
#include "API.h"
// #include <stdio.h>
//#include <string>
//#include <iostream>
//#include <vector>

struct gameObject
{
  int x;
  int y;
  int color;
};

class botUart{
private:
  gameObject yellow;
  gameObject red;
  gameObject blue;
  char workingData[1000];
  char finishedData[1000];
  uint8_t* rcvChar;
  int arrCount;
  bool finalNum = false;

public:

  botUart()
  {
    yellow.color = 0;
    blue.color = 1;
    red.color = 2;
    usartInit(uart1, 9600, SERIAL_DATABITS_8);
    this->rcvChar =(uint8_t*) malloc (sizeof(uint8_t)*1);
    // *this->rcvChar = '&';
    this->arrCount = 0;
    clearFinArr();
    clearWorkArr();
  };
  int pow(int base, int exp)
  {
    if(exp == 0)
    {
      return 1;
    }
    else if (exp % 2)
    {
      return base * pow(base, exp - 1);
    }
    else
    {
      int tmp = pow(base, exp / 2);
      return tmp * tmp;
    }

  }
  // void cristianObjValues(){
  //   int counter = 0;
  //
  //   for(counter = 99;x>-1;)
  //
  //
  //
  // };
  void setObVals()
  {
    int i = 0;
    int comCnt = 0;
    int powNum = 0;
    int numTot = 0;

    while(this->finishedData[i] != '&')
    {
      // printf("in loop\n");
      // printf("Character is currently: %c\n",this->finishedData[i]);
      i++;
    }
    printf("STOPPED, ENCOUNTERED '&'\n");
    i--; //i is at the index of the first encountered ;
    while(i >= -1)
    {
      if(this->finishedData[i] != ',' && (i != -1))
      {
        char tmp = ((char)this->finishedData[i] - '0');
        int tmp2 = (int)tmp;
        // printf("%d",tmp2);
        // printf("%d\n",tmp);
        numTot = numTot + (tmp2 * pow(10, powNum));
        // numTot = numTot + ((this->finishedData[i]) * pow(10, powNum));
        powNum++;
      }
      else
      {
        switch(comCnt)
        {
          case 0: this->red.y = numTot;
          case 1: this->red.x = numTot;
          case 2: this->blue.y = numTot;
          case 3: this->blue.x = numTot;
          case 4: this->yellow.y = numTot;
          case 5: this->yellow.x = numTot;
        }
        comCnt++;
        powNum = 0;
        numTot = 0;
      }
      i--;
    }
  }

  void printObVals()
  {
    printf("%d,%d,%d,%d,%d,%d--\n",this->yellow.x,this->yellow.y,this->blue.x,this->blue.y,this->red.x,this->red.y);
  }

  void printStr()
  {
    int i = 0;
    // printf("%c", 't');
    while (this->finishedData[i] != '&')
    {
      // printf("%c", 't');
      printf("%c", this->finishedData[i]);
      i++;
    }
    printf("\n");
  }

  void clearFinArr()
  {
    int i = 0;
    while(i < 99)
    {
      this->finishedData[i] = '&';
      i++;
    }
  }
  void clearFinArr(int num)
  {
    int i = num;
    while(i < 99)
    {
      this->finishedData[i] = '&';
      i++;
    }
  }
  void clearWorkArr()
  {
    int i = 0;
    while(i < 99)
    {
      this->workingData[i] = '&';
      i++;
    }
  }
  void clearWorkArr(int num)
  {
    int i = num;
    while(i < 99)
    {
      this->workingData[i] = '&';
      i++;
    }
  }

  void readData()
  {
    int i = 0;
    fread(this->rcvChar,sizeof(uint8_t),1,uart1);
    // printf("%c\n", (char)*this->rcvChar);
    if(*this->rcvChar == '&')
    {
      // this->finishedData = this->workingData;
      clearFinArr();
      while(i < 99)
      {
        if(this->workingData[i] == '&')
          // continue;
          break;
        this->finishedData[i] = this->workingData[i];
        i++;
      }
      clearFinArr(i);
      clearWorkArr();
      this->arrCount = 0;
    }
    else
    {
      this->workingData[this->arrCount] = *this->rcvChar;
      // this->workingData = this->workingData + this->rcvChar;
      this->arrCount++;
    }
  };
  void runUART()
  {
    this->readData();
    this->setObVals();
    this->printObVals();
  }
};
#endif
