#ifndef Fieldbh
    #define Fieldbh

#include "BASIC.h"
#include "ALL.h"


class FieldBehaviour
{
public:
    Data dat;
    FieldBehaviour(/* args */);
    ~FieldBehaviour();
    void allBehave();
    void allMove();
   // Data* getData(){return &dat;}
    vector<Creature*> getNearCreatures(vector<float> pos, float r);
};

#endif
