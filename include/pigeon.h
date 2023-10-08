#ifndef Pigeonh
    #define Pigeonh


#include <vector>
#include <iostream>
#include "creature.h"
#include "fieldb.h"
#include "coord.h"
using namespace std;
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

    static  vector<float> coef; // sep align cohes turnfactor carDist carDodge
    static  vector<float> searchRad;    // sep align cohes edges
    static  vector<float> Margin;//left right bottom top
public:
    Pigeon(Vec3Cord, FieldBehaviour*);
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