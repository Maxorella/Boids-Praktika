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
        prevstress=stress;
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
    prevstress=stress;
    speedVector.x=0; speedVector.y=0; speedVector.z=0;
    this->StressControl(); // отвечает за стресс и взлёт-посадку
    this->GoToFood(); // отвечает за полёт/приближение к еде
    this->Alignment();
    this->Separation();
    this->Cohesion();
    this->AvoidEdges();
    this->CarDodge();
    this->FlyHigher();
    this->LookPlaceLand();
    this->AvoidObstacles();
}

void Pigeon::move()
{
    speed=speedVector;
    pos.x+=speed.x* dat.getTimeMultpl();
    pos.y+=speed.y* dat.getTimeMultpl();
    pos.z+=speed.z* dat.getTimeMultpl();
    if(flying){// модификация для облёта препятствий
        Creature* obst = fieldBeh->getHighestObstacle(this->pos,0.1);
        if (obst!= nullptr){
            if(obst->getpos().z > this->pos.z){
                this->pos.z = obst->getpos().z+0.1;
            }
        }
    }
    if(flying && pos.z <searchRad.StartHeight) {
        pos.z = searchRad.StartHeight; //  защита от кротов
    }
}

void Pigeon::LookPlaceLand() {
    if(pos.z > 3){

        float xPosAvg = 0;
        float yPosAvg = 0;
        int neighbCount = 0;
        vector<Creature*> nearCr = fieldBeh->getNearCreatures(pos, searchRad.LookPlaceInRad);
        for(int i=0; i<nearCr.size(); i++)
        {
            xPosAvg+=nearCr[i]->getpos().x;
            yPosAvg+=nearCr[i]->getpos().y;
            neighbCount+=1;
        }
        if(nearCr.size()!=0){ // рядом никого нету проверка чтобы в бесконечность не уходить
            xPosAvg/=(float)neighbCount;
            yPosAvg/=(float)neighbCount;
            speedVector.x-=(xPosAvg-pos.x)*coef.LookPlaceTolandC; // улёт от птиц
            speedVector.y-=(yPosAvg-pos.y)*coef.LookPlaceTolandC;
        }
    }
}


void Pigeon::AvoidObstacles(){

    vector<Creature*> obstles = fieldBeh->GetNearObstacles(this->pos,searchRad.ObstSearchRadius);
    for(int i=0; i<obstles.capacity(); i++){
        Creature* obst = obstles[i];
        if(pos.x > obst->getpos().x){
            speedVector.x+=  (searchRad.ObstSearchRadius-(dat.distance2d(this->pos,obst->getpos())-obst->getRadius()))*coef.ObstacleDodgeC;// расстояние до края!!
        } else{
            speedVector.x-=  (searchRad.ObstSearchRadius-(dat.distance2d(this->pos,obst->getpos())-obst->getRadius()))*coef.ObstacleDodgeC;// расстояние до края!!
        }
        if(pos.y > obst->getpos().y){
            speedVector.y+=  (searchRad.ObstSearchRadius-(dat.distance2d(this->pos,obst->getpos())-obst->getRadius()))*coef.ObstacleDodgeC;// расстояние до края!!
        }
        else{
            speedVector.y-=  (searchRad.ObstSearchRadius-(dat.distance2d(this->pos,obst->getpos())-obst->getRadius()))*coef.ObstacleDodgeC;// расстояние до края!!
        }
    }
}

void Pigeon::FlyHigher(){
    if (flying){
        if (stress<coef.PorogStress+coef.StressGoEarthFast){ // TODO: подправить снижение если стресс закончился
            speedVector.z-= coef.StremitelnoSniz; // стремительно снижаемся
        }
        speedVector.z += (stress-prevstress)*coef.StressHeightProp;
    }
}



void Pigeon::GoToFood() {
    Creature* nearFood =fieldBeh->getNearFood(pos,searchRad.foodSearchRad);
    //cout<< dat.distance2d(nearFood->getpos(),pos) << endl;
    if(nearFood== nullptr){
        return;
    }
    if (!flying && dat.distance2d(nearFood->getpos(),pos)<0.2f){
        dat.RemoveFood(nearFood); // если пора скушать еду!!!
        return;
    }



    Vec3Cord govector; // птица - еда вектор
    govector.x =nearFood->getpos().x- pos.x;
    govector.y =  nearFood->getpos().y -pos.y;
    govector.z = nearFood->getpos().z-pos.z;
    float lent = sqrt(govector.x*govector.x+govector.y*govector.y+govector.z*govector.z);
    govector.x = govector.x/lent;
    govector.y = govector.y/lent; // получили единичный вектор направления
    govector.z = govector.z/lent; // получили единичный вектор направления
    speedVector.x+=coef.FoodCoefXY*govector.x;
    speedVector.y+=coef.FoodCoefXY*govector.y; // идём в сторону еды
    if(flying && pos.z < searchRad.FlyToFoodHeight){ // летим к еде если не слишком высоко // TODO подумать как лучше
            speedVector.z += govector.z * coef.FoodFlyingCoef; //TODO могут стать кротами
    }
        //float procent = dat.distance(pos,nearFood->getpos())/searchRad.foodSearchRad; // насколько мы близки к еде от 0 до 1 НЕ НУЖНО
}

void Pigeon::StressAdder() {
    vector<Creature *> onEarth = fieldBeh->getNearCreaturesEarth(this->pos, searchRad.MinstressBirdDist);
    for (int i = 0; i < onEarth.size(); i++) {
        stress += (dat.distance2d(this->pos, onEarth[i]->getpos()) - searchRad.MaxstressBirdDist) /
                  (searchRad.MinstressBirdDist - searchRad.MaxstressBirdDist) * coef.streesGainerC;
    }

    vector<Creature *> onFly = fieldBeh->getNearCreaturesFlying(this->pos, searchRad.MinstressBirdDist);
    for (int i = 0; i < onFly.size(); i++) {
        stress += (dat.distance(this->pos, onFly[i]->getpos()) - searchRad.MaxstressBirdDist) /
                  (searchRad.MinstressBirdDist - searchRad.MaxstressBirdDist) * coef.streesGainerC *
                  coef.FlyingStressMultp;
    }

    Creature *carr = dat.getCar();
    if (dat.distance(pos, carr->getpos()) < searchRad.stressCarDist) { // стресс от машины
        stress += (searchRad.stressCarDist - dat.distance(pos, carr->getpos())) *coef.CarStressMultp * coef.streesGainerC;
    }



}

void Pigeon::StressReducer() {
    stress-=coef.PassiveStressReduce;
    stress-=pos.z * coef.StressHeightReduceC; // TODO дополнительное уменьш стресса от высоты
    if (stress<0){
        stress=0; // стресс меньше нуля не может быть
    }
    //cout << stress << endl;

}

void Pigeon::StressControl() {
    this->StressAdder();
    this->StressReducer();
    if(stress>coef.PorogStress){
        this->StartFlying();
    } else if(stress < coef.PorogStress && pos.z < searchRad.LandingHeight){ //  pos.z < 0.3f - высота посадки
        this->EndFlying();
    }


}

void Pigeon::StartFlying() {
    flying= true; // взлетаем
    pos.z = searchRad.StartHeight; //нач высота отрыва
}

void Pigeon::EndFlying() {
    flying= false; // садимся
    pos.z = 0; //посадка

}


void Pigeon::CarDodge(){
    Creature* car = dat.getCar();
    Vec3Cord carPos = car->getpos();
    Vec3Cord PigCarVec; // вектор направления (нач)птица-машина(конец)
    PigCarVec.x = carPos.x - pos.x;
    PigCarVec.y = carPos.y - pos.y;
    PigCarVec.z = carPos.z - pos.z;


    if(dat.distance(pos,carPos)<searchRad.carDist){
        speedVector.x+=  -(searchRad.carDist-PigCarVec.x)  *coef.carDodge;
        speedVector.y+=  -(searchRad.carDist-PigCarVec.y)  *coef.carDodge;

        if (flying){
            speedVector.z+=(searchRad.carDist-PigCarVec.z)  *coef.carDodge;
        }

    }
}


void Pigeon::Separation()
{
    if (flying){
        vector<Creature*> nearCreatures = fieldBeh->getNearCreaturesFlying(pos, searchRad.sep);
        float closeDx=0;
        float closeDy=0;
        float closeDz=0;
        for(int i=0; i<nearCreatures.size(); i++)
        {
            closeDx+=pos.x - nearCreatures[i]->getpos().x;
            closeDy+=pos.y - nearCreatures[i]->getpos().y;
            closeDz+=pos.z - nearCreatures[i]->getpos().z;
        }
        speedVector.x += closeDx*coef.sep;
        speedVector.y += closeDy*coef.sep;
      //  speedVector.z += closeDz*coef.sep; // TODO тут может быть ошибка


    }
    else{

        vector<Creature*> nearCreatures = fieldBeh->getNearCreaturesEarth(pos, searchRad.sep);
        float closeDx=0;
        float closeDy=0;
        for(int i=0; i<nearCreatures.size(); i++)
        {
            closeDx+=pos.x - nearCreatures[i]->getpos().x;
            closeDy+=pos.y - nearCreatures[i]->getpos().y;
        }
        speedVector.x += closeDx*coef.sep;
        speedVector.y += closeDy*coef.sep;
    }
    
}
void Pigeon::Alignment()
{
    if (flying){
        float xVelocityAvg = 0;
        float yVelocityAvg = 0;
        float zVelocityAvg = 0;

        int neighbCount = 0;
        vector<Creature*> nearCr = fieldBeh->getNearCreaturesFlying(pos, searchRad.align);
        for(int i=0; i<nearCr.size(); i++)
        {
            xVelocityAvg+=nearCr[i]->getspeed().x;
            yVelocityAvg+=nearCr[i]->getspeed().y;
            zVelocityAvg+=nearCr[i]->getspeed().z;
            neighbCount+=1;
        }
        if (neighbCount>0)
        {
            xVelocityAvg = xVelocityAvg/(float)neighbCount;
            yVelocityAvg = yVelocityAvg/(float)neighbCount;
        }
        speedVector.x += (xVelocityAvg - speed.x)*coef.align;
        speedVector.y += (yVelocityAvg - speed.y)*coef.align;
        speedVector.z += (zVelocityAvg - speed.z)*coef.align;





    } else{
        float xVelocityAvg = 0;
        float yVelocityAvg = 0;
        int neighbCount = 0;
        vector<Creature*> nearCr = fieldBeh->getNearCreaturesEarth(pos, searchRad.align);
        for(int i=0; i<nearCr.size(); i++)
        {
            xVelocityAvg+=nearCr[i]->getspeed().x;
            yVelocityAvg+=nearCr[i]->getspeed().y;
            neighbCount+=1;
        }
        if (neighbCount>0)
        {
            xVelocityAvg = xVelocityAvg/(float)neighbCount;
            yVelocityAvg = yVelocityAvg/(float)neighbCount;
        }
        speedVector.x += (xVelocityAvg - speed.x)*coef.align;
        speedVector.y += (yVelocityAvg - speed.y)*coef.align;

    }



}

void Pigeon::Cohesion()
{
    if (flying){
        float xPosAvg = 0;
        float yPosAvg = 0;
        float zPosAvg = 0;
        int neighbCount = 0;
        vector<Creature*> nearCr = fieldBeh->getNearCreaturesFlying(pos, searchRad.cohes);
        for(int i=0; i<nearCr.size(); i++)
        {
            xPosAvg+=nearCr[i]->getpos().x;
            yPosAvg+=nearCr[i]->getpos().y;
            zPosAvg+=nearCr[i]->getpos().z;
            neighbCount+=1;
        }
        if(nearCr.size()!=0) { // рядом никого нету проверка чтобы в бесконечность не уходить
            xPosAvg /= (float) neighbCount;
            yPosAvg /= (float) neighbCount;
            zPosAvg /= (float) neighbCount;
            speedVector.x += (xPosAvg - pos.x) * coef.cohes;
            speedVector.y += (yPosAvg - pos.y) * coef.cohes;
            speedVector.z += (zPosAvg - pos.z) * coef.cohes;
        }


    } else{


        float xPosAvg = 0;
        float yPosAvg = 0;
        int neighbCount = 0;
        vector<Creature*> nearCr = fieldBeh->getNearCreaturesEarth(pos, searchRad.cohes);
        for(int i=0; i<nearCr.size(); i++)
        {
            xPosAvg+=nearCr[i]->getpos().x;
            yPosAvg+=nearCr[i]->getpos().y;
            neighbCount+=1;
        }
        if(nearCr.size()!=0){ // рядом никого нету проверка чтобы в бесконечность не уходить
            xPosAvg/=(float)neighbCount;
            yPosAvg/=(float)neighbCount;
            speedVector.x+=(xPosAvg-pos.x)*coef.cohes;
            speedVector.y+=(yPosAvg-pos.y)*coef.cohes;
        }

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
