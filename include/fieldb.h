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

    Creature* getNearFood(Vec3Cord nearPos, float inRadius);

};

#endif
