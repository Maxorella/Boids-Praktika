#include "ALL.h"
#include "BASIC.h"



int Input::getBirdFile(string filename)
{
    ifstream inpf;
    inpf.open(filename, ifstream::in);
    if(!inpf.is_open())
    {
        cout << "Error: Bird file wasn't opened." << endl;
        return -1;
    }
    string line, subst;
    
    while (getline(inpf, line))
    {
        stringstream ss(line);
        vector <float> v;
        v.clear();
        while (getline(ss, subst, ' '))  //ss >> name >> course >> grade;?????

        {
            v.push_back(atof(subst));
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
    while (getline(inpf, line))
    {
        stringstream ss(line);
        vector <float> v;
        v.clear();

        while (getline(ss, subst, ' '))
        {
            v.push_back(atof(subst));
        }
        dat.setinpfile(v);
    }
    inpf.close();
    return 1;
}
