#ifndef INPClass
    #define INPClass

#include "ALL.h"
#include "BASIC.h"

using namespace std;

class Input
{
private:
    Data dat;
public:
    int getBirdFile(string filename);
    int getCarFile(string filename);
};

#endif