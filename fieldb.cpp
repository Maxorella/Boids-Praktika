#include "fieldb.h"
#include "data.h"
#include "coord.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

void FieldBehaviour::allBehave(){
    for(int i=0; i<dat.getPigInMeadowSize(); i++)
    {
        dat.getPigeon(i)->behave();
    }
    dat.getCar()->behave();
}

void FieldBehaviour::allMove(){
    for(int i=0; i<dat.getPigInMeadowSize(); i++)
    {
        dat.getPigeon(i)->move();
    }
    dat.getCar()->move();
}


vector<Creature*> FieldBehaviour::getNearCreatures(Vec3Cord nearPos, float inRadius)
{
    vector<Creature*> foundCreatures;
     for(int i=0; i<dat.getPigInMeadowSize(); i++)
    {
        Vec3Cord pigPos = dat.getPigeon(i)->getpos();
        float dist = sqrt(pow(pigPos.x-nearPos.x,2)+ pow( pigPos.y-nearPos.y,2));
        if (dist <= inRadius && dist!=0)
        {
            foundCreatures.push_back(dat.getPigeon(i));
        }
    }
    return foundCreatures;
}


FieldBehaviour::FieldBehaviour(/* args */)
{
    
}

FieldBehaviour::~FieldBehaviour()
{
}