#ifndef Modelh
    #define Modelh

#include <string>
#include <iostream>
#include "output.h"
#include "fieldb.h"

class Model{
private:
    string birdFileName;
    OutputController outController;
    float timer=0;
    float sliceTime=60;
    Data dat;
    FieldBehaviour* behavController;
public:
    Model(FieldBehaviour*, string);
    void simulate();
    ~Model();
};



#endif
