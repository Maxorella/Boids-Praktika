#include <vector>
#include <iostream>
#include "pigeon.h"
using namespace std;
#include "coord.h"


CoefStruct Pigeon::coef;
searchRadStruct Pigeon::searchRad;
MarginStruct Pigeon::Margin;

Pigeon::Pigeon(Vec3Cord startPos, FieldBehaviour* f): fieldBeh(f){ //pos(startPos),
    if(startPos.z!=0){ // если птица летает
        stress=startPos.z*coef.StressInitCoef;
        flying= true;
        pos=startPos;
    } else{
        pos = startPos; // TODO можно и начальный стресс задать
    }

}

Vec3Cord Pigeon::getpos(){ return pos;}
Vec3Cord Pigeon::getspeed(){ return speed;}


bool Pigeon::isFlying(){
    return flying;
}

void Pigeon::behave()
{
    speedVector.x=0; speedVector.y=0; speedVector.z=0;
    this->StressControl(); // отвечает за стресс и взлёт-посадку
    this->GoToFood(); // отвечает за полёт/приближение к еде
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

void Pigeon::GoToFood() {
    Creature* nearFood =fieldBeh->getNearFood(pos,searchRad.foodSearchRad);
    //cout<< dat.distance2d(nearFood->getpos(),pos) << endl;
    if(nearFood== nullptr){
        return;
    }
    if (dat.distance2d(nearFood->getpos(),pos)<0.3f){
        dat.RemoveFood(nearFood); // если пора скушать еду!!!
        return;
    }

    //float procent = dat.distance(pos,nearFood->getpos())/searchRad.foodSearchRad; // насколько мы близки к еде от 0 до 1 НЕ НУЖНО
    Vec3Cord govector;
    govector.x = nearFood->getpos().x - pos.x;
    govector.y = nearFood->getpos().y - pos.y;
    float lent = sqrt(govector.x*govector.x+govector.y*govector.y);
    govector.x = govector.x/lent;
    govector.y = govector.y/lent; // получили единичный вектор направления
    speedVector.x+=coef.FoodCoef*govector.x;
    speedVector.y+=coef.FoodCoef*govector.y; // идём в сторону еды

}

void Pigeon::StressAdder() {
    vector<Creature*> onEarth = fieldBeh->getNearCreaturesEarth(this->pos,searchRad.MinstressBirdDist);
    for(int i=0; i<onEarth.size();i++){
        stress+= (dat.distance2d(this->pos,onEarth[i]->getpos())-searchRad.MaxstressBirdDist)/(searchRad.MinstressBirdDist-searchRad.MaxstressBirdDist) * coef.streesGainerC;
    }

    vector<Creature*> onFly = fieldBeh->getNearCreaturesFlying(this->pos,searchRad.MinstressBirdDist);
    for(int i=0; i<onFly.size();i++){
        stress+= (dat.distance(this->pos,onFly[i]->getpos())-searchRad.MaxstressBirdDist)/(searchRad.MinstressBirdDist-searchRad.MaxstressBirdDist) * coef.streesGainerC * coef.FlyingStressMultp;
    }


}

void Pigeon::StressReducer() {
    stress-=coef.PassiveStressReduce;
    if (stress<0){
        stress=0; // стресс меньше нуля не может быть
    }


}

void Pigeon::StressControl() {
/*
    Creature* car = dat.getCar();
    Vec3Cord carPos = car->getpos();
    vector<Creature*> nearCreatures = fieldBeh->getNearCreatures(pos, searchRad.stressBirdDist);
    for(int i=0; i<nearCreatures.size(); i++)
    {
        int multupl;
        if nearCreatures // d
        stress+= searchRad.stressBirdDist
        // прибавляем стресс от находящихся рядом птиц!!!
    }
*/
}

void Pigeon::StartFlying() {

}

void Pigeon::EndFlying() {

}


void Pigeon::CarDodge(){
    Creature* car = dat.getCar();
    Vec3Cord carPos = car->getpos();
    if(dat.distance(pos,carPos)<searchRad.carDist){
        speedVector.x+=carPos.x * (dat.distance(pos,carPos)-searchRad.carDist)*coef.carDodge;
        speedVector.y+=carPos.y * (dat.distance(pos,carPos)-searchRad.carDist)*coef.carDodge;
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
    if(nearCr.size()!=0){ // рядом никого нету проверка чтобы в бесконечность не уходить
        xPosAvg/=neighbCount;
        yPosAvg/=neighbCount;
        speedVector.x+=(xPosAvg-pos.x)*coef.cohes;
        speedVector.x+=(yPosAvg-pos.y)*coef.cohes;
    }
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
