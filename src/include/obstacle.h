//
// Created by User on 09.12.2023.
//

#ifndef BOIDS_OBSTACLE_H
#define BOIDS_OBSTACLE_H

//
// Created by User on 26.11.2023.
//



#include <vector>
#include <iostream>
#include "creature.h"
#include "fieldb.h"
#include "coord.h"
using namespace std;


class Obstacle: public Creature
{
private:
    Vec3Cord pos; ///
    float radius;

    FieldBehaviour* fieldBeh;
    Data dat;
    // Each boid attempts to avoid running into other boids. If two or more boids get too close to one another
    //Each boid attempts to match the velocity of other boids inside its visible range.
    // Each boid steers gently toward the center of mass of other boids within its visible range.


public:
    virtual float getRadius();
    Obstacle(Vec4Cord, FieldBehaviour*);
    ~Obstacle();
    virtual Vec3Cord getpos();
    virtual Vec3Cord getspeed();
    void behave();
    void move();
};


#endif //BOIDS_OBSTACLE_H
