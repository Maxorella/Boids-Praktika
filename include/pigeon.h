#ifndef Pigeonh
    #define Pigeonh


#include "BASIC.h"
class FieldBehaviour;
class Data;
class Pigeon: public Creature
{
private:
    vector<float> pos;
    vector<float> speed;
    vector<float> speedVector;
    FieldBehaviour* fieldBeh;
    Data dat;
  //  Data* dat;
    // Each boid attempts to avoid running into other boids. If two or more boids get too close to one another
    //Each boid attempts to match the velocity of other boids inside its visible range.
    // Each boid steers gently toward the center of mass of other boids within its visible range.

    static  vector<float> coef; // sep align cohes turnfactor carDist carDodge
    static  vector<float> searchRad;    // sep align cohes edges
    static  vector<float> Margin;//left right bottom top
public:
    Pigeon(vector<float>, FieldBehaviour*);
    ~Pigeon();
    void behave();
    void move();
    vector<float> getpos();
    void Separation();
    void Alignment();
    void Cohesion();
    vector<float> getspeed();
    void AvoidEdges();
    void CarDodge();
};


#endif