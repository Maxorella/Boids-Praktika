#include "car.h"
#include "data.h"
#include "coord.h"
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


Car::Car(){}

Car::Car(Vec3Cord p){
    pos = p;
    targetPos = p;
}

Car::~Car(){};


Vec3Cord Car::getpos(){
    return pos;
}

Vec3Cord Car::getspeed()
{
    return speed;
}
void Car::behave(){
    speedVector.x=0;
    speedVector.y=0;
    if(dat.distance(pos,targetPos)<0.2){
        if (pointNumToReach<dat.getCarPointCount()){
            targetPos=dat.getCarPoint(pointNumToReach);
            pointNumToReach++;
        }
    }
    speedVector.x=(targetPos.x-pos.x)/dat.distance(targetPos,pos);
    speedVector.y=(targetPos.x-pos.x)/dat.distance(targetPos,pos);
    speed= speedVector;
}

void Car::move(){
    pos.x+=speed.x*dat.getTimeMultpl()*speedCoef*dat.getTimeMultpl();
    pos.y+=speed.y*dat.getTimeMultpl()*speedCoef*dat.getTimeMultpl();
}