#include <vector>
#include <iostream>
#include "pigeon.h"
using namespace std;

vector<float> Pigeon::coef; // sep align cohes turnfactor carDist carDodge
vector<float> Pigeon::searchRad;    // sep align cohes edges
vector<float> Pigeon::Margin;//left right bottom top
Pigeon::Pigeon(vector<float> p, FieldBehaviour* f): pos(p), fieldBeh(f){
    
   // pos.push_back(0); //TODO: multipe init!!!
   // pos.push_back(0);
    
    speed.push_back(0); 
    speed.push_back(0);
   
    speedVector.push_back(0); 
    speedVector.push_back(0);
    
    
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

vector<float> Pigeon::getpos(){ return pos;}
vector<float> Pigeon::getspeed(){ return speed;}

void Pigeon::behave()
{
   this->Alignment();
   this->Separation();
   this->Cohesion();
   this->AvoidEdges();
   this->CarDodge();
}

void Pigeon::move()
{
    speed=speedVector;
    pos[0]+=speed[0]* dat.getdeltaTime();
    pos[1]+=speed[1]* dat.getdeltaTime();
}

void Pigeon::CarDodge(){
    Creature* c = dat.getCar();
    vector<float> carp = c->getpos();
    if(dat.distance(pos,carp)<coef[4]){
        speedVector[0]+=carp[0] * (dat.distance(pos,carp)-coef[4])*coef[5];
        speedVector[1]+=carp[1] * (dat.distance(pos,carp)-coef[4])*coef[5];
    }

}
void Pigeon::Separation()
{
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad[0]);
    float closeDx=0;
    float closeDy=0;
    for(int i=0; i<nearCr.size(); i++)
    {
        closeDx+=pos[0] - nearCr[i]->getpos()[0];
        closeDy+=pos[1] - nearCr[i]->getpos()[1];
    }
    speedVector[0] += closeDx*coef[0];
    speedVector[1] += closeDy*coef[0];
    
}
void Pigeon::Alignment()
{
    float xvelavg = 0;
    float yvelavg = 0;
    int neighb = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad[1]);
    for(int i=0; i<nearCr.size(); i++)
    {
        xvelavg+=nearCr[i]->getspeed()[0];
        yvelavg+=nearCr[i]->getspeed()[1];
        neighb+=1;
    }
    if (neighb>0)
    {
        xvelavg = xvelavg/neighb;
        yvelavg = yvelavg/neighb;
    }
    speedVector[0] += (xvelavg - speed[0])*coef[1];
    speedVector[1] += (yvelavg - speed[1])*coef[1];
}

void Pigeon::Cohesion()
{
    float xposavg = 0;
    float yposavg = 0;
    int neighb = 0;
    vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad[2]);
    for(int i=0; i<nearCr.size(); i++)
    {
        xposavg+=nearCr[i]->getpos()[0];
        yposavg+=nearCr[i]->getpos()[1];
        neighb+=1;
    }
    xposavg/=neighb;
    yposavg/=neighb;
    speedVector[0]+=(xposavg-pos[0])*coef[2];
    speedVector[1]+=(yposavg-pos[1])*coef[2];
}
void Pigeon::AvoidEdges()
{
    if (pos[0] < Margin[0])        //left
    speedVector[0] = speedVector[0] + coef[3];
    if (pos[0] > Margin[1])
        speedVector[0] = speedVector[0] - coef[3];
    if (pos[1] > Margin[2])
        speedVector[1] = speedVector[1] - coef[3];
    if (pos[1] < Margin[3])
        speedVector[1] = speedVector[1] + coef[3];
}
Pigeon::~Pigeon()
{
}
