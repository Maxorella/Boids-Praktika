#ifndef Pigeonh
    #define Pigeonh

#include <vector>
#include <iostream>
#include "creature.h"
#include "fieldb.h"
#include "coord.h"
using namespace std;


struct CoefStruct {
    float sep = 0.08; // отдаления от ближних
    float align = 0.05; //выравниванния скоростей
    float cohes = 0.02; // выравнивания к центру масс
    float turnfactor = 0.3; // поворот от углов
    float carDodge = 0.12; // уворот от машины
    float streesGainerC=0.3; // коэф добавления стресса
    float FlyingStressMultp = 1; // во сколько раз летаюшие больше раздражают
    float CarStressMultp = 6; //во сколько раз МАШИНА больше раздражают
    float PorogStress=10; // пороговый стресс для взлёта
    float StressInitCoef=2; // на каждую единицу z*coef - начальный стресс птицы
    float FoodCoefXY=0.3; // приближение
    float PassiveStressReduce = 2; // пассивное уменьш стресса
    float StressHeightReduceC = 20; // уменьшение от высоты
    float FoodFlyingCoef =0.4; // в полёте насколько приближаемся к еде!
    float StressHeightProp = 0.3f;//пропорц изм стресса и высоты
    float LookPlaceTolandC = 0.6f; // поиск места для посадки
    float ObstacleDodgeC = 0.2f;
    float StremitelnoSniz = 0.15; // дополнительно быстро снижаемся если стресса мало
    float StressGoEarthFast = 10; // прибавка к пороговому стрессу, чтобы начать быстрое снижение
};

struct searchRadStruct {
    int sep = 5; // радиус отдаления от ближних
    int align = 7;  // радиус выравниванния скоростей
    int cohes = 10; // радиус выравнивания к центру масс
    float carDist = 8.0; // дистанция боязни машины
    float MinstressBirdDist = 6; // начал раст прибавления стресса
    float MaxstressBirdDist = 1; // конечн раст прибавления стресса
    float stressCarDist = 10; // начал дист стресса от машины
    float foodSearchRad = 30; // радиус поиска еды
    //float MaxSpeedFoodRad = 2;
    float StartHeight = 0.3f; // начальная высота отрыва
    float LandingHeight = 0.4f;
    float LookPlaceInRad = 10;
    float ObstSearchRadius = 3; // нач дистанция уворота от препятствия
    float FlyToFoodHeight = 3; // высота с которой начинаем задумываться о еде
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
    double prevstress=0;
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
    void FlyHigher();
    void LookPlaceLand();
    void AvoidObstacles();
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
