#include "car.h"
#include <iostream>
#include <vector>
using namespace std;


Car::Car()
{
    pos.push_back(0); pos.push_back(0); 
    speedVector.push_back(0); speedVector.push_back(0); speedVector.push_back(0);
    speed.push_back(0); speed.push_back(0); speed.push_back(0);
}

Car::Car(vector <float> p){
    pos = p;
    speedVector.push_back(0); speedVector.push_back(0); speedVector.push_back(0);
    speed.push_back(0); speed.push_back(0); speed.push_back(0);
    targetPos = pos;
}

Car::~Car(){};


vector<float> Car::getpos(){return pos;}

vector<float> Car::getspeed(){return speed;}
void Car::behave(){
    if(dat.distance(pos,targetPos)<0.2){
        if (pointN<dat.getpointCount()){
            targetPos=dat.getCarPoint(pointN);
            pointN++;
        }
    }
    speedVector[0]=(targetPos[0]-pos[0])/dat.distance(targetPos,pos);
    speedVector[1]=(targetPos[1]-pos[1])/dat.distance(targetPos,pos);
    speed=speedVector;
}

void Car::move(){
    pos[0]+=speed[0]*dat.getdeltaTime()*speedCoef;
    pos[1]+=speed[1]*dat.getdeltaTime()*speedCoef;
}