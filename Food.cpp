#include <vector>
#include <iostream>
#include "food.h"
using namespace std;
#include "coord.h"


Food::Food(Vec3Cord startPos, FieldBehaviour* f): pos(startPos), fieldBeh(f){

    // pos.push_back(0); //TODO: multipe init!!!
    // pos.push_back(0);

}

Vec3Cord Food::getpos(){ return pos;}
Vec3Cord Food::getspeed(){return Vec3Cord();}
void Food::behave(){}
void Food::move(){}
Food::~Food(){};
