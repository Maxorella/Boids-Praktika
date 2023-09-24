#ifndef INPClass
    #define INPClass

#include "BASIC.h"
class Data;
using namespace std;

class Input_F
{
private:
    Data dat;
public:
    int getBirdFile(string filename);
    int getCarFile(string filename);
};

#endif