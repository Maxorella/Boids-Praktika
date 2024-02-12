#include "car.h"
#include "data.h"
#include "coord.h"
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


//Car::Car(){}

Car::Car(Vec3Cord p, FieldBehaviour* beh){
    pos = p;
    targetPos = p;
    fieldb = beh;
}

Car::~Car(){}


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
    //cout << pos.x<< " " << pos.y << " "<< pos.z << " cur car pos" <<endl;
    //cout << targetPos.x<< " " << targetPos.y << " "<< targetPos.z << " cur car pos" <<endl;

    //cout << dat.distance2d(pos,targetPos) << " distance" << endl;
    if(GoGeomtr){
        float xavg=0;
        float yavg=0;
        vector<Creature*> birds = fieldb->getNearCreaturesEarth(this->pos, 100);
        for(int j=0;j<birds.size();j++){
            xavg+=birds[j]->getpos().x;
            yavg+=birds[j]->getpos().y;
        }
        if (birds.size()==0){
            xavg=1;
            yavg=1;
        } else{
            xavg=xavg/birds.size();
            yavg=yavg/birds.size();
        }
        if(xavg>pos.x){
            speedVector.x=xavg-pos.x;
        } else{
            speedVector.x=xavg-pos.x;
        }

        if(yavg>pos.y){
            speedVector.y=yavg-pos.y;
        } else{
            speedVector.y=yavg-pos.y;
        }
        speed=speedVector;

    } else{
        if(dat.distance2d(pos,targetPos)<0.2f){
            if (pointNumToReach<dat.getCarPointCount()){
                targetPos=dat.getCarPoint(pointNumToReach);
                pointNumToReach++;
            } else{
                GoGeomtr=true;
                speedVector.x=1;
                speedVector.y=1;
                speed=speedVector;
                return;
            }
        }
        speedVector.x=(targetPos.x-pos.x)/dat.distance(targetPos,pos);
        speedVector.y=(targetPos.y-pos.y)/dat.distance(targetPos,pos);
        speed=speedVector;
    }
}

void Car::move(){
    pos.x+=speed.x*dat.getTimeMultpl()*speedCoef;
    pos.y+=speed.y*dat.getTimeMultpl()*speedCoef;
}