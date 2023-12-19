#include "data.h"
#include "coord.h"
#include <cmath>
#include <vector>
#include "food.h"
#include <iostream>
using namespace std;

 vector<float> Data::weighs; // INIT??
 float Data::timeMultiplier=0.05f;
 //vector<Creature*> Data::meadow;
 vector<Creature*> Data::pigeonsInMeadow;
vector<Vec3Cord > Data::startPigeonsPoses; // - координаты птиц
 Creature* Data::car;
vector<Vec3Cord > Data::carPosesInstruction; // - координаты машин
//int Data::pointCount;
 vector<Vec3Cord> Data::startFoodPoses;
 vector<Creature*> Data::FoodInMeadow;
 vector<Vec4Cord> Data::startObstPoses; // - иниц коорд препятств
 vector<Creature*> Data::obstacles; // - позиции препятствий



Data::Data(){weighs.push_back(1.0); weighs.push_back(2.0); weighs.push_back(1.0);} //TODO: multipe init!

int Data::getPigInMeadowSize(){return pigeonsInMeadow.size();}

Creature* Data::getPigeon(int pos) {return pigeonsInMeadow[pos];}

void Data::setPigToMeadow(Creature* v) { pigeonsInMeadow.push_back(v);}

Creature* Data::getCar(){return car;}

void Data::setCar(Creature* c){car = c;}

//vector<float> Data::getweights(){ return weighs; }

void Data::setPigStartPos(Vec3Cord v){startPigeonsPoses.push_back(v);}

Vec3Cord Data::getPigStartPos(int pos){return startPigeonsPoses[pos];}

int Data::getPigeonsCount(){return startPigeonsPoses.size();}

//int Data::getcarfilesize(){return carPosesInstruction.size();};

float Data::distance(Vec3Cord vec3a, Vec3Cord vec3b ){ return sqrt(pow(vec3a.x-vec3b.x,2)+pow(vec3a.y-vec3b.y,2)+pow(vec3a.z-vec3b.z,2)); }
float Data::distance2d(Vec3Cord vec3a, Vec3Cord vec3b ){ return sqrt(pow(vec3a.x-vec3b.x,2)+pow(vec3a.y-vec3b.y,2)); }

Vec3Cord Data::getCarPoint(int pos){ return carPosesInstruction[pos];}

void Data::setCarPoint(Vec3Cord v){ carPosesInstruction.push_back(v); return;}

int Data::getCarPointCount(){return carPosesInstruction.size();}

float Data::getTimeMultpl(){return timeMultiplier;}

void Data::AddFoodStart(Vec3Cord v){startFoodPoses.push_back(v);}
Vec3Cord Data::GetFoodStart(int pos){ return startFoodPoses[pos];}
int Data::GetStartFoodCount(){return startFoodPoses.size();}
int Data::GetFoodCount(){return FoodInMeadow.size();}

void Data::SetFood(Creature* v){FoodInMeadow.push_back(v); }

Creature* Data::GetFoodPos(int pos){return FoodInMeadow[pos];}


void Data::setObstStartPos(Vec4Cord x){
    startObstPoses.push_back(x);
}

Vec4Cord Data::getObstStartPos(int ind){
    return startObstPoses[ind];
}


Creature* Data::getObst(int ind){
    return obstacles[ind];
}


void Data::setObst(Creature* ob){
    obstacles.push_back(ob);
}

int Data::getObstCount(){
    return startObstPoses.capacity();
}

bool Data::RemoveFood(Creature* ptr){
    for(int i=0;i<FoodInMeadow.size();i++){
        if (ptr==FoodInMeadow[i]){
            FoodInMeadow.erase(FoodInMeadow.begin()+i); //ToDo убедиться в правильности
            ptr->~Creature();
            return true;
        }
    }
    return false;
}