
#include "Data.h"
#include "output.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void OutputController::createSlice()
{
    Data dat;
    static int i = 1;
    Vec3Cord v;
    ofstream outstrm(to_string(i)+".txt");
    if(!outstrm.is_open())
    {
        cout << "Error: file wasn't created." << endl;
        return;
    }

    Vec3Cord outCarPos =dat.getCar()->getpos();
    outstrm << outCarPos.x << " " << outCarPos.y << " " << outCarPos.z << " " << std::endl;

    for ( int j = 0 ; j < dat.getPigInMeadowSize(); j++ )
    {
        Vec3Cord outPigPos =dat.getPigeon(j)->getpos();
        outstrm << outPigPos.x << " " << outPigPos.y << " " << outPigPos.z << " " << std::endl;
    }
    outstrm << dat.GetFoodCount() << std::endl;
    for ( int j = 0 ; j < dat.GetFoodCount(); j++ )
    {
        Vec3Cord outFoodPos =dat.GetFoodPos(j)->getpos();
        outstrm << outFoodPos.x << " " << outFoodPos.y << std::endl;
    }














    outstrm.close();
    i++;
    return;
}
