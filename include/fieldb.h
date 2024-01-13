#ifndef Fieldbh
    #define Fieldbh
#include <vector>
#include "creature.h"
#include "data.h"
#include "coord.h"
#include <cmath>

class FieldBehaviour
{
public:
    Data dat;
    FieldBehaviour();
    ~FieldBehaviour();
    void allBehave();
    void allMove();
    vector<Creature*> getNearCreatures(Vec3Cord nearPos, float inRadius);
    vector<Creature*> getNearCreaturesEarth(Vec3Cord nearPos, float inRadius);
    vector<Creature*> getNearCreaturesFlying(Vec3Cord nearPos, float inRadius);
    //vector<Creature*> getHighest(Vec3Cord nearPos, float inRadius);
    Creature* getHighestObstacle(Vec3Cord nearPos, float inRadius);//TODO
    Creature *getNearFood(Vec3Cord nearPos, float inRadius);
    vector<Creature*> GetNearObstacles(Vec3Cord nearPos, float inRadius);
};

#endif
