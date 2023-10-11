#include <vector>
#include <iostream>
#include "pigeon.h"
using namespace std;
#include "coord.h"

struct Pigeon::coef {
    float sep = 0.1;
    float align = 0.05;
    float cohes = 0.02;
    float turnfactor = 0.2;
    float carDist = 1.0;
    float carDodge = 0.3;
};

struct Pigeon::searchRad {
    int sep = 3;
    int align = 5;
    int cohes = 10;
    int edges = 20;
};

struct Pigeon::Margin {
    int left = -30;
    int right = 30;
    int bottom = -30;
    int top = 30;
};

Pigeon::Pigeon(Vec3Cord startPos, FieldBehaviour* f): pos(startPos), fieldBeh(f){
    
   // pos.push_back(0); //TODO: multipe init!!!
   // pos.push_back(0);
   pos = startPos;
   fieldBeh = f;
}

Vec3Cord Pigeon::getpos(){ return pos;}
Vec3Cord Pigeon::getspeed(){ return speed;}

void Pigeon::behave()
{
    speedVector.x=0; speedVector.y=0; speedVector.z=0;
    this->Alignment();
    this->Separation();
    this->Cohesion();
    this->AvoidEdges();
    this->CarDodge();
}

void Pigeon::move()
{
    speed=speedVector;
    pos.x+=speed.x* dat.getTimeMultpl();
    pos.y+=speed.y* dat.getTimeMultpl();
}

void Pigeon::CarDodge(){
    Creature* car = dat.getCar();
    Vec3Cord carPos = car->getpos();
    if(dat.distance(pos,carPos)<coef.carDist){
        speedVector.x+=carPos.x * (dat.distance(pos,carPos)-coef.carDist)*coef.carDodge;
        speedVector.y+=carPos.y * (dat.distance(pos,carPos)-coef.carDist)*coef.carDodge;
    }

}
void Pigeon::Separation()
{
    vector<Creature*> nearCreatures = fieldBeh->getNearCreatures(pos, searchRad.sep);
    float closeDx=0;
    float closeDy=0;
    for(int i=0; i<nearCreatures.size(); i++)
    {
        closeDx+=pos.x - nearCreatures[i]->getpos().x;
        closeDy+=pos.x - nearCreatures[i]->getpos().y;
    }
    speedVector.x += closeDx*coef.sep;
    speedVector.y += closeDy*coef.sep;
    
}
void Pigeon::Alignment()
{
    float xVelocityAvg = 0;
    float yVelocityAvg = 0;
    int neighbCount = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad.align);
    for(int i=0; i<nearCr.size(); i++)
    {
        xVelocityAvg+=nearCr[i]->getspeed().x;
        yVelocityAvg+=nearCr[i]->getspeed().y;
        neighbCount+=1;
    }
    if (neighbCount>0)
    {
        xVelocityAvg = xVelocityAvg/neighbCount;
        yVelocityAvg = yVelocityAvg/neighbCount;
    }
    speedVector.x += (xVelocityAvg - speed.x)*coef.align;
    speedVector.y += (yVelocityAvg - speed.y)*coef.align;
}

void Pigeon::Cohesion()
{
    float xPosAvg = 0;
    float yPosAvg = 0;
    int neighbCount = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad.cohes);
    for(int i=0; i<nearCr.size(); i++)
    {
        xPosAvg+=nearCr[i]->getpos().x;
        yPosAvg+=nearCr[i]->getpos().y;
        neighbCount+=1;
    }
    xPosAvg/=neighbCount;
    yPosAvg/=neighbCount;
    speedVector.x+=(xPosAvg-pos.x)*coef.cohes;
    speedVector.x+=(yPosAvg-pos.y)*coef.cohes;
}
void Pigeon::AvoidEdges()
{
    if (pos.x < Margin.left)        //left
    speedVector.x = speedVector.x + coef.turnfactor;
    if (pos.x > Margin.right)
        speedVector.x = speedVector.x - coef.turnfactor;
    if (pos.y < Margin.bottom)
        speedVector.y = speedVector.y - coef.turnfactor;
    if (pos.y > Margin.top)
        speedVector.y = speedVector.y + coef.turnfactor;
}
Pigeon::~Pigeon()
{
}

