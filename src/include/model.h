#ifndef Modelh
    #define Modelh

#include <string>
#include <iostream>
#include "output.h"
#include "fieldb.h"

class Model{
private:
    string birdFileName;
    string outfile;
    OutputController outController;
    float timer=0;
    float sliceTime=60;
    Data dat;
    FieldBehaviour* behavController;
public:
    Model(FieldBehaviour*, string, string);
    void simulate();
    ~Model();
};



#endif
