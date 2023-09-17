#include <creature.h>
#include <iostream>
#include <vector>
#include <data.h>
#include <cmath>
class Car:public Creature
{
private:
    Data dat;
    int pointN=0;
    vector<float> pos{0, 0};
    vector<float> targetPos{0, 0};
    vector<float> speedVector{0,0};
    vector<float> speed{0,0};
    float speedCoef=0.1f;
    //float distance(vector<float>, vector<float>);
public:
     vector<float> getpos(){return pos;}
     vector<float> getspeed(){return speed;}
    Car();
    virtual ~Car();
    void behave();
    void move();
};


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