#ifndef Creatureh
    #define Creatureh
#include "ALL.h"
#include "BASIC.h"


class Creature
{
public:
    Creature();
    virtual ~Creature();
public:
    virtual void behave()=0;
    virtual void move()=0;
    virtual vector<float> getpos()=0;
    virtual vector<float> getspeed()=0;
    
};


#endif