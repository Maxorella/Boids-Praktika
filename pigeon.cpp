#include <vector>
#include <iostream>
#include "pigeon.h"
using namespace std;
#include "coord.h"
vector<float> Pigeon::coef; // sep align cohes turnfactor carDist carDodge
vector<float> Pigeon::searchRad;    // sep align cohes edges
vector<float> Pigeon::Margin;//left right bottom top
Pigeon::Pigeon(Vec3Cord startPos, FieldBehaviour* f): pos(startPos), fieldBeh(f){
    
   // pos.push_back(0); //TODO: multipe init!!!
   // pos.push_back(0);

    searchRad.push_back(3); 
    searchRad.push_back(5);
    searchRad.push_back(10);
    searchRad.push_back(20);
  //  Pigeon::searchRad={3, 5, 10, 20};
  //  Pigeon::Margin={-30, 30, -30, 30};

    Margin.push_back(-30);
    Margin.push_back(30);
    Margin.push_back(-30);
    Margin.push_back(30);


 //   Pigeon::coef={0.1, 0.05, 0.02, 0.2, 1, 0.3};
    coef.push_back(0.1);
    coef.push_back(0.05);
    coef.push_back(0.02);
    coef.push_back(0.2);
    coef.push_back(1);
    coef.push_back(0.3);
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
    if(dat.distance(pos,carPos)<coef[4]){
        speedVector.x+=carPos.x * (dat.distance(pos,carPos)-coef[4])*coef[5];
        speedVector.y+=carPos.y * (dat.distance(pos,carPos)-coef[4])*coef[5];
    }

}
void Pigeon::Separation()
{
    vector<Creature*> nearCreatures = fieldBeh->getNearCreatures(pos, searchRad[0]);
    float closeDx=0;
    float closeDy=0;
    for(int i=0; i<nearCreatures.size(); i++)
    {
        closeDx+=pos.x - nearCreatures[i]->getpos().x;
        closeDy+=pos.x - nearCreatures[i]->getpos().y;
    }
    speedVector.x += closeDx*coef[0];
    speedVector.y += closeDy*coef[0];
    
}
void Pigeon::Alignment()
{
    float xVelocityAvg = 0;
    float yVelocityAvg = 0;
    int neighbCount = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad[1]);
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
    speedVector.x += (xVelocityAvg - speed.x)*coef[1];
    speedVector.y += (yVelocityAvg - speed.y)*coef[1];
}

void Pigeon::Cohesion()
{
    float xPosAvg = 0;
    float yPosAvg = 0;
    int neighbCount = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad[2]);
    for(int i=0; i<nearCr.size(); i++)
    {
        xPosAvg+=nearCr[i]->getpos().x;
        yPosAvg+=nearCr[i]->getpos().y;
        neighbCount+=1;
    }
    xPosAvg/=neighbCount;
    yPosAvg/=neighbCount;
    speedVector.x+=(xPosAvg-pos.x)*coef[2];
    speedVector.x+=(yPosAvg-pos.y)*coef[2];
}
void Pigeon::AvoidEdges()
{
    if (pos.x < Margin[0])        //left
    speedVector.x = speedVector.x + coef[3];
    if (pos.x > Margin[1])
        speedVector.x = speedVector.x - coef[3];
    if (pos.y < Margin[2])
        speedVector.y = speedVector.y - coef[3];
    if (pos.y > Margin[3])
        speedVector.y = speedVector.y + coef[3];
}
Pigeon::~Pigeon()
{
}
