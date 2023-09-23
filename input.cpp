#include "ALL.h"
#include "BASIC.h"



int Input::getBirdFile(string filename)
{
    ifstream inpf;
    inpf.open(filename, std::ifstream::in);
    if(!inpf.is_open())
    {
        cout << "Error: Bird file wasn't opened." << endl;
        return -1;
    }
    string line, subst;
    vector <float> v{};
    while (getline(inpf, line))
    {
        stringstream ss(line);
        v={};
        while (getline(ss, subst, ' '))  //ss >> name >> course >> grade;?????

        {
            v.push_back((float)subst);
        }
        dat.setinpfile(v);
    }
    inpf.close();
    return 1;
}

int Input::getCarFile(string filename)
{
    ifstream inpf(filename);
    inpf.open("test.txt", std::ifstream::in);

    if(!inpf.is_open())
    {
        cout << "Error: Car file wasn't opened." << endl;
        return -1;
    }
    string line, subst;
    vector <float> v{};
    while (getline(inpf, line))
    {
        stringstream ss(line);
        v={};
        while (getline(ss, subst, ' '))
        {
            v.push_back((float)subst);
        }
        dat.setinpfile(v);
    }
    inpf.close();
    return 1;
}
