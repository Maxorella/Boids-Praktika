
#include "ALL.h"
#include "BASIC.h"

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