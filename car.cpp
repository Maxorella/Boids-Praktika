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
    cout << pos.x<< " " << pos.y << " "<< pos.z << " cur car pos" <<endl;
    cout << targetPos.x<< " " << targetPos.y << " "<< targetPos.z << " cur car pos" <<endl;

    cout << dat.distance2d(pos,targetPos) << " distance" << endl;
    if(dat.distance(pos,targetPos)<0.2f){
        if (pointNumToReach<dat.getCarPointCount()){
            targetPos=dat.getCarPoint(pointNumToReach);
            pointNumToReach++;
        }
    }
    speedVector.x=(targetPos.x-pos.x)/dat.distance(targetPos,pos);
    speedVector.y=(targetPos.y-pos.y)/dat.distance(targetPos,pos);
    speed= speedVector;
}

void Car::move(){
    pos.x+=speed.x*dat.getTimeMultpl()*speedCoef;
    pos.y+=speed.y*dat.getTimeMultpl()*speedCoef;
}