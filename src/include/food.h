//
// Created by User on 26.11.2023.
//

#ifndef BOIDS_FOOD_H
#define BOIDS_FOOD_H

#include <vector>
#include <iostream>
#include "creature.h"
#include "fieldb.h"
#include "coord.h"
using namespace std;


class Food: public Creature
{
private:
    Vec3Cord pos;
    FieldBehaviour* fieldBeh;
    Data dat;
    // Each boid attempts to avoid running into other boids. If two or more boids get too close to one another
    //Each boid attempts to match the velocity of other boids inside its visible range.
    // Each boid steers gently toward the center of mass of other boids within its visible range.


public:
    Food(Vec3Cord, FieldBehaviour*);
    ~Food();
    Vec3Cord getpos();
    Vec3Cord getspeed();
    void behave();
    void move();
};



#endif //BOIDS_FOOD_H
