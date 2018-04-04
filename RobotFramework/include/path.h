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
    this->maxStep = 10;
  };
  path(CartesianVector initialPos){
    this->waypointList.push_back(initialPos);
    this->minStep = 0;
    this->maxStep = 10;
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
  int size(){
    return this->waypointList.size();
  }
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
    int length = (int)(sqrt(pow(abs(xShift),2)+pow(abs(yShift),2))/step);
    xShift = (xShift/abs(xShift))*step;
    printf("xShift: %f\n",xShift);
    yShift = (yShift/abs(yShift))*step;

    CartesianVector tempPos;
    tempPos.x = pos.x;
    tempPos.y = pos.y;
    for(int i=1;i<length+1;i++){
        tempPos.x += xShift;
        tempPos.y += yShift;
        addWaypoint(tempPos);
    }
  };

  CartesianVector get_waypointAt(int index){
      return this->waypointList[index];
  };

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
  void printWaypoints(){

    for(int i =0;i<(int)(this->waypointList.size());i++){

      printf(" %f,", get_waypointAt(i).x);
      printf("\n");
    }
  };
};

#endif
