#include "ALL.h"
#include "BASIC.h"



int Input::getBirdFile(string filename)
{
    ifstream inpf;
    inpf.open(filename);
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
       
        while (ss >> subst) { // Extract word from the stream.
            v.push_back(stof(subst));
        }
        
        dat.setinpfile(v);
    }
    inpf.close();
    return 1;
}

int Input::getCarFile(string filename)
{
    ifstream inpf;
    inpf.open(filename);

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
            v.push_back(stof(subst));
        }
        dat.setcarfile(v);
    }
    inpf.close();
    return 1;
}
