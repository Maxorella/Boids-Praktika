#include "input.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "coord.h"
using namespace std;
int InputController::getBirdFile(string filename)
{
    ifstream inpfile;
    inpfile.open(filename);
    if(!inpfile.is_open())
    {
        cout << "Error: Bird file wasn't opened." << endl;
        return -1;
    }
    string line, subst;
    
    while (getline(inpfile, line))
    {
        stringstream strStream(line);
        Vec3Cord readenV;
        int i = 0;
        while (getline(strStream, subst, ' '))
        {
            if (i % 3 == 0)
                readenV.x = (stof(subst));
            else
            {
                if (i % 3 == 1)
                    readenV.y = (stof(subst));
                else
                    readenV.z = (stof(subst));
            }
            i++;
        }
        if (i != 3)
        {
            cout << "Error: uncorrect file format." << endl;
            return -2;
        }
        dat.setPigStartPos(readenV);
    }
    inpfile.close();
    return 1;
}

int InputController::getCarFile(string filename)
{
    ifstream inpfile;
    inpfile.open(filename);

    if(!inpfile.is_open())
    {
        cout << "Error: Car file wasn't opened." << endl;
        return -1;
    }
    string line, subst;
    
    while (getline(inpfile, line))
    {
        stringstream strStream(line);
        Vec3Cord readenV;
        int i = 0;
        while (getline(strStream, subst, ' '))
        {
            if (i % 3 == 0)
                readenV.x = (stof(subst));
            else
            {
                if (i % 3 == 1)
                    readenV.y = (stof(subst));
                else
                    readenV.z = (stof(subst));
            }
            i++;
        }
        if (i != 3)
        {
            cout << "Error: uncorrect file format." << endl;
            return -2;
        }
        dat.setCarPoint(readenV);
    }
    inpfile.close();
    return 1;
}

