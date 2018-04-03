#ifndef PATH_H
#define PATH
#include "./utility/vector.h"
#include <vector>
#include <API.h>
#include "math.h"
class path{

private:
  std::vector<CartesianVector> waypointList;
  int minStep;
  int maxStep;
public:

  path(){
    this->minStep = 0;
    this->maxStep = 1000;
  };
  path(CartesianVector initialPos){
    this->waypointList.push_back(initialPos);
    this->minStep = 0;
    this->maxStep = 1000;
  };
  path(double x, double y, int timeStamp){
    CartesianVector initialPos;
    initialPos.x = x;
    initialPos.y = y;
    initialPos.timeStamp = timeStamp;
    this->waypointList.push_back(initialPos);
    this->minStep = 0;
    this->maxStep = 1000;
  };
  std::vector<CartesianVector> get_waypointList(){
    return this->waypointList;
  };

  void addWaypoint(CartesianVector vector){
    this->waypointList.push_back(vector);
  };

  void fillWaypointList(CartesianVector pos, CartesianVector targetPos, double step = 0){
    double xShift = targetPos.x - pos.x;
    double yShift = targetPos.y - pos.y;
    if(abs(step) < abs(this->minStep)){
      step = this->minStep;
    }
    if(abs(step) > abs(this->maxStep)){
      step = this->maxStep;
    }
    int length = sqrt(pow(abs(xShift),2)+pow(abs(yShift),2))/step;
    xShift = (xShift/abs(xShift))*step;
    yShift = (yShift/abs(yShift))*step;

    std::vector<CartesianVector> tempList;
    tempList.resize(length);
    tempList[0] = pos;
    for(int i=1; i < (int)tempList.size(); i++)
    {
        tempList[i].x = tempList[i-1].x+xShift;
        tempList[i].y = tempList[i-1].y+yShift;
        addWaypoint(tempList[i]);
    }
  };

  CartesianVector get_waypointAt(int index){
    if(index < (int)(this->waypointList.size())){
      return this->waypointList[index];
    }
    else{
      printf("Index %d is out of bounds. Max length is: %d\n",index, this->waypointList.size()-1);
    }
  }

  void set_minStep(int minStep){
    this->minStep = minStep;
  };
  int get_minStep(){
    return this->minStep;
  };
  void set_maxStep(int maxStep){
    this->maxStep = maxStep;
  };
  int get_maxStep(){
    return this->maxStep;
  };

};

#endif
