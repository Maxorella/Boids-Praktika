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
    float carDist = 1.0;
    float carDodge = 0.3;
};

struct searchRadStruct {
    int sep = 3;
    int align = 5;
    int cohes = 10;
    int edges = 20;
};

struct MarginStruct {
    int left = -30;
    int right = 30;
    int bottom = -30;
    int top = 30;
};


class Pigeon: public Creature
{
private:
    Vec3Cord pos;
    Vec3Cord speed;
    Vec3Cord speedVector;
    FieldBehaviour* fieldBeh;
    Data dat;
    // Each boid attempts to avoid running into other boids. If two or more boids get too close to one another
    //Each boid attempts to match the velocity of other boids inside its visible range.
    // Each boid steers gently toward the center of mass of other boids within its visible range.

    
public:
    Pigeon(Vec3Cord, FieldBehaviour*);
    static CoefStruct coef; // sep align cohes turnfactor carDist carDodge
    static searchRadStruct searchRad;    // sep align cohes edges
    static MarginStruct Margin;//left right bottom top
    ~Pigeon();
    void behave();
    void move();
    Vec3Cord getpos();
    void Separation();
    void Alignment();
    void Cohesion();
    Vec3Cord getspeed();
    void AvoidEdges();
    void CarDodge();

};


#endif
