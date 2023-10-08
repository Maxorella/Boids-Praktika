#include "input.h"
#include <string>
#include <vector>
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
        vector <float> v; //TODO: в обработке сделать сразу Vec3Cord  и саму обработку сделать на правильность файлов
        v.clear();
       
        while (strStream >> subst) { // Extract word from the stream.
            v.push_back(stof(subst));
        }
        Vec3Cord readenV;
        readenV.x = v[0];
        readenV.y = v[1];
        readenV.z = v[2];
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
        vector <float> v;
        v.clear();

        while (getline(strStream, subst, ' '))
        {
            v.push_back(stof(subst));
        } //TODO: в обработке сделать сразу Vec3Cord  и саму обработку сделать на правильность файлов
        Vec3Cord readenV;
        readenV.x = v[0];
        readenV.y = v[1];
        readenV.z = v[2];
        dat.setCarPoint(readenV);
    }
    inpfile.close();
    return 1;
}
