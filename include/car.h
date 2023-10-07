#ifndef Carh
    #define Carh

#include <vector>
#include <iostream>
using namespace std;
#include "creature.h"
#include "data.h"


class Car: public Creature
{
private:
    Data dat;
    int pointN=1;
    vector<float> pos;
    vector<float> targetPos;
    vector<float> speedVector;
    vector<float> speed;
    float speedCoef=0.1f;
public:
     vector<float> getpos();
     vector<float> getspeed();
    Car();
    Car(vector <float>);
    virtual ~Car();
    void behave();
    void move();
};

#endif