#ifndef Creatureh
    #define Creatureh
#include <vector>
#include <iostream>
#include "coord.h"
using namespace std;
class Creature
{
public:
    Creature(){};
    virtual ~Creature(){};
    virtual void behave()=0;
    virtual void move()=0;
    virtual Vec3Cord getpos()=0;
    virtual Vec3Cord getspeed()=0;
    virtual bool isFlying(){ return false;};
    virtual  float getRadius(){return 0;}
};


#endif