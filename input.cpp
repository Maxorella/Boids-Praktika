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
        exit(-1);
    }
    string line, subst;
    
    while (getline(inpfile, line))
    {
        stringstream strStream(line);
        Vec3Cord readenV;
        int count_vars = 0;
        while (getline(strStream, subst, ' '))
        {
            if (subst.find_first_not_of("-.0123456789") == string::npos) {
                if (count_vars % 3 == 0)
                    readenV.x = (stof(subst));
                else
                {
                    if (count_vars % 3 == 1)
                        readenV.y = (stof(subst));
                    else
                        readenV.z = (stof(subst));
                }
                count_vars++;
            }
            else {
                cout << "Error: uncorrect file format." << endl;
                exit(-2);
            }
        
        }
        if (count_vars != 3)
        {
            cout << "Error: uncorrect file format." << endl;
            exit(-2);
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
        exit(-1);
    }
    string line, subst;
    
    while (getline(inpfile, line))
    {
        stringstream strStream(line);
        Vec3Cord readenV;
        int count_vars = 0;
        while (getline(strStream, subst, ' '))
        {
            if (subst.find_first_not_of("-.0123456789") == string::npos) {
                if (count_vars % 3 == 0)
                    readenV.x = (stof(subst));
                else
                {
                    if (count_vars % 3 == 1)
                        readenV.y = (stof(subst));
                    else
                        readenV.z = (stof(subst));
                }
                count_vars++;
            }
            else {
                cout << "Error: uncorrect file format." << endl;
                exit(-2);
            }
        
        }
        if (count_vars != 3)
        {
            cout << "Error: uncorrect file format." << endl;
            exit(-2);
        }
        dat.setCarPoint(readenV);
    }
    inpfile.close();
    return 1;
}
