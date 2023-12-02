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
        double dist = sqrt(pow(pigPos.x-nearPos.x,2)+ pow( pigPos.y-nearPos.y,2)+pow( pigPos.z-nearPos.z,2));
        if (dist <= inRadius && dist!=0)
        {
            foundCreatures.push_back(dat.getPigeon(i));
        }
    }
    return foundCreatures;
}

vector<Creature*> FieldBehaviour::getNearCreaturesEarth(Vec3Cord nearPos, float inRadius)
{
    vector<Creature*> foundCreatures;
    for(int i=0; i<dat.getPigInMeadowSize(); i++)
    {
        Vec3Cord pigPos = dat.getPigeon(i)->getpos();
        double dist = sqrt(pow(pigPos.x-nearPos.x,2)+ pow( pigPos.y-nearPos.y,2));
        if (dist <= inRadius && dist!=0 && !dat.getPigeon(i)->isFlying())
        {
            foundCreatures.push_back(dat.getPigeon(i));
        }
    }
    return foundCreatures;
}

vector<Creature*> FieldBehaviour::getNearCreaturesFlying(Vec3Cord nearPos, float inRadius)
{
    vector<Creature*> foundCreatures;
    for(int i=0; i<dat.getPigInMeadowSize(); i++)
    {
        Vec3Cord pigPos = dat.getPigeon(i)->getpos();
        double dist = sqrt(pow(pigPos.x-nearPos.x,2)+ pow( pigPos.y-nearPos.y,2)+pow( pigPos.z-nearPos.z,2));
        if (dist <= inRadius && dist!=0 && dat.getPigeon(i)->isFlying())
        {
            foundCreatures.push_back(dat.getPigeon(i));
        }
    }
    return foundCreatures;
}
/*
vector<Creature*> FieldBehaviour::getNearFood(Vec3Cord nearPos, float inRadius){
    vector<Creature*> foundCreatures;
    for(int i=0; i<dat.GetFoodCount(); i++)
    {
        Vec3Cord FoodPos = dat.GetFoodPos(i)->getpos();
        double dist = sqrt(pow(FoodPos.x-nearPos.x,2)+ pow( FoodPos.y-nearPos.y,2)+pow( FoodPos.z-nearPos.z,2));
        if (dist <= inRadius && dist!=0)
        {
            foundCreatures.push_back(dat.GetFoodPos(i));
        }
    }
    return foundCreatures;
}
 */

Creature* FieldBehaviour::getNearFood(Vec3Cord nearPos, float inRadius){
    Creature* foundFood = nullptr;
    for(int i=0; i<dat.GetFoodCount(); i++)
    {
        Vec3Cord FoodPos = dat.GetFoodPos(i)->getpos();
        double dist = dat.distance(FoodPos,nearPos);
        if (dist <= inRadius  && dist!=0)
        {
            if (foundFood==nullptr){
                foundFood=dat.GetFoodPos(i);
            } else if ( dat.distance(nearPos,foundFood->getpos()) > dist  ){ // нашли еду поближе
                foundFood = dat.GetFoodPos(i);
            }
        }
    }
    return foundFood;
}


FieldBehaviour::FieldBehaviour(/* args */)
{
    
}

FieldBehaviour::~FieldBehaviour()
{
}