#ifndef Carh
    #define Carh
#include "ALL.h"
#include "BASIC.h"


class Car:public Creature
{
private:
    Data dat;
    int pointN=0;
    vector<float> pos;
    vector<float> targetPos;
    vector<float> speedVector;
    vector<float> speed;
    float speedCoef=0.1f;
    //float distance(vector<float>, vector<float>);
public:
     vector<float> getpos(){return pos;}
     vector<float> getspeed(){return speed;}
    Car(){
        pos.push_back(0); pos.push_back(0); 
        speedVector.push_back(0); speedVector.push_back(0);
        speed.push_back(0); speed.push_back(0);
    }
    virtual ~Car();
    void behave();
    void move();
};

#endif