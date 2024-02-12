#ifndef INPClass
    #define INPClass
#include <string>
#include <iostream>
#include "Data.h"
#include "coord.h"
class InputController
{
private:
    Data dat;
 //   bool ReadBird();
  //  bool ReadCar();
  //  bool ReadFood();
    void parseField(string Mystr);
    Vec3Cord parsePos(string Mystr);
    void parseComas(string Mystr);
    void parseFood(string Mystr);
    void parseCar(string Mystr);
    void parseBird(string Mystr);
    void parseObst(std::string  Mystr);
    Vec4Cord parse4Pos(string Mystr);// работает
    
public:
    int getBirdFile(string filename);
    int getCarFile(string filename);
    int ReadInputFile(string filename);
};

#endif