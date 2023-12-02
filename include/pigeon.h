#ifndef Pigeonh
    #define Pigeonh

#include <vector>
#include <iostream>
#include "creature.h"
#include "fieldb.h"
#include "coord.h"
using namespace std;


struct CoefStruct {
    float sep = 0.1;
    float align = 0.05;
    float cohes = 0.02;
    float turnfactor = 0.2;
    float carDodge = 2;
    float streesGainerC=0.1; // коэф добавления стресса
    float FlyingStressMultp = 2; // во сколько раз летаюшие больше раздражают
    float CarStressMultp = 5; //во сколько раз МАШИНА больше раздражают
    float PorogStress=10; // пороговый стресс для взлёта
    float StressInitCoef=2; // на каждую единицу z*coef - начальный стресс птицы
    float FoodCoef=0.4;
    float PassiveStressReduce = 2; // пассивное уменьш стресса
};

struct searchRadStruct {
    int sep = 3;
    int align = 5;
    int cohes = 10;
    float carDist = 5.0; // дистанция боязни машины
    float MinstressBirdDist = 20;
    float MaxstressBirdDist = 2;
    float stressCarDist = 30;
    float foodSearchRad = 20; // радиус поиска еды
    float MaxSpeedFoodRad = 2;
   // int edges = 20;
};

struct MarginStruct {
    MarginStruct(){}
    MarginStruct(int UP, int DOWN, int RIGHT, int LEFT):top(UP),bottom(DOWN),right(RIGHT),left(LEFT){}
    int left = -20;
    int right = 20;
    int bottom = -20;
    int top = 20;
};


class Pigeon: public Creature
{
private:
    Vec3Cord pos;
    Vec3Cord speed;
    Vec3Cord speedVector;
    bool flying = false;
    double stress = 0;
    FieldBehaviour* fieldBeh;
    Data dat;
    // Each boid attempts to avoid running into other boids. If two or more boids get too close to one another
    //Each boid attempts to match the velocity of other boids inside its visible range.
    // Each boid steers gently toward the center of mass of other boids within its visible range.

    void Separation();
    void Alignment();
    void Cohesion();
    void AvoidEdges();
    void CarDodge();
    void StressControl();
    void GoToFood();
    void StartFlying();
    void EndFlying();
    void StressAdder();
    void StressReducer();
    
public:
    Pigeon(Vec3Cord, FieldBehaviour*);
    static CoefStruct coef; // sep align cohes turnfactor carDist carDodge
    static searchRadStruct searchRad;    // sep align cohes edges
    static MarginStruct Margin;//left right bottom top
    ~Pigeon();
    void behave();
    void move();
    Vec3Cord getpos();
    Vec3Cord getspeed();
    virtual bool isFlying();
};


#endif
