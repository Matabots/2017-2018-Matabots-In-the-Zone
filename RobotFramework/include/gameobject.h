#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "API.h"
class gameobject{

private:
  int x;
  int y;

public:

      gameobject(){

      }
      void setX(int x){
        this->x = x;
      }
      int getX(){
        return this->x;
      }
      void setY(int y){
        this->y = y;
      }
      int getY(){
        return this->y;
      }
};

#endif
