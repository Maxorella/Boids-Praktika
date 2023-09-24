
#include "BASIC.h"
#include "ALL.h"


void FieldBehaviour::allBehave(){
    for(int i=0; i<dat.getPDataSize(); i++)
    {
        dat.getPigeon(i)->behave();
    }
    dat.getCar()->behave();
}

void FieldBehaviour::allMove(){
    for(int i=0; i<dat.getPDataSize(); i++)
    {
        dat.getPigeon(i)->move();
    }
    dat.getCar()->move();
}


vector<Creature*> FieldBehaviour::getNearCreatures(vector<float> pos, float r)
{
    vector<Creature*> out;
     for(int i=0; i<dat.getPDataSize(); i++)
    {
        vector<float> pPos = dat.getPigeon(i)->getpos();
        float dist = sqrt(pow(pPos[0]-pos[0],2)+ pow( pPos[1]-pos[1],2)); 
        if (dist <= r && dist!=0)
        {
            out.push_back(dat.getPigeon(i));
        }
    }
    return out;
}


FieldBehaviour::FieldBehaviour(/* args */)
{
}

FieldBehaviour::~FieldBehaviour()
{
}