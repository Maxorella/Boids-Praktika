#ifndef Modelh
    #define Modelh

#include "BASIC.h"
class Data;
class Output_F;
class FieldBehaviour;
class Model{
private:
    Output_F outobj;
    float timer=0;
    float sliceTime=40;
    Data dat;
    FieldBehaviour* beh;
public:
    Model(FieldBehaviour* b);
    void simulate();
    ~Model();
};



#endif
