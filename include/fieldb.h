#ifndef Fieldbh
    #define Fieldbh
#include <vector>
#include "creature.h"
#include "data.h"
#include "coord.h"
class FieldBehaviour
{
public:
    Data dat;
    FieldBehaviour();
    ~FieldBehaviour();
    void allBehave();
    void allMove();
    vector<Creature*> getNearCreatures(Vec3Cord nearPos, float inRadius);
};

#endif
