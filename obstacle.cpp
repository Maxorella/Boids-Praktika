#include <vector>
#include <iostream>
#include "obstacle.h"
using namespace std;
#include "coord.h"


Obstacle::Obstacle(Vec4Cord startPos, FieldBehaviour* f): fieldBeh(f){
    pos.x=startPos.x;
    pos.y=startPos.y;
    pos.z=startPos.z;
    radius=startPos.r;
    // pos.push_back(0); //TODO: multipe init!!!
    // pos.push_back(0);

}



Vec3Cord Obstacle::getpos(){ return pos;}
Vec3Cord Obstacle::getspeed(){return Vec3Cord();}
float Obstacle::getRadius(){ return radius;}

void Obstacle::behave(){}
void Obstacle::move(){}
Obstacle::~Obstacle(){}


