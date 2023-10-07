#ifndef INPClass
    #define INPClass
#include <string>
#include <iostream>
#include "Data.h"
class Input_F
{
private:
    Data dat;
public:
    int getBirdFile(string filename);
    int getCarFile(string filename);
};

#endif