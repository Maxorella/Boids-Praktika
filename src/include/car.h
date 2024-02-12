#ifndef Carh
    #define Carh

#include <vector>
#include <iostream>
using namespace std;
#include "creature.h"
#include "data.h"
#include "coord.h"
#include "fieldb.h"

class Car: public Creature
{
private:
    Data dat;
    int pointNumToReach=1;
    Vec3Cord pos;
    Vec3Cord targetPos;
    Vec3Cord speedVector;
    Vec3Cord speed;
    float speedCoef=0.3f;
    FieldBehaviour* fieldb;
    bool GoGeomtr= false;
public:
    Vec3Cord getpos();
    Vec3Cord getspeed();
    //Car(FieldBehaviour*);
    Car(Vec3Cord, FieldBehaviour*);
    virtual ~Car();
    void behave();
    void move();
};

#endif