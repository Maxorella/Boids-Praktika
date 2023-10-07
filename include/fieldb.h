#ifndef Fieldbh
    #define Fieldbh
#include <vector>
#include "creature.h"
#include "data.h"

class FieldBehaviour
{
public:
    Data dat;
    FieldBehaviour();
    ~FieldBehaviour();
    void allBehave();
    void allMove();
    vector<Creature*> getNearCreatures(vector<float> pos, float r);
};

#endif
