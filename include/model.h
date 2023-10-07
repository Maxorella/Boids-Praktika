#ifndef Modelh
    #define Modelh

#include <string>
#include <iostream>
#include "output.h"
#include "fieldb.h"

class Model{
private:
    string birdfilename;
    string carfilename;
    Output_F outobj;
    float timer=0;
    float sliceTime=60;
    Data dat;
    FieldBehaviour* beh;
public:
    Model(FieldBehaviour*, string, string);
    void simulate();
    ~Model();
};



#endif
