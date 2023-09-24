#ifndef Modelh
    #define Modelh

#include "BASIC.h"
#include "ALL.h"


class Model{
private:
    string birdfilename;
    string carfilename;
    Output_F outobj;
    float timer=0;
    float sliceTime=40;
    Data dat;
    FieldBehaviour* beh;
public:
    Model(FieldBehaviour*, string, string);
    void simulate();
    ~Model();
};



#endif
