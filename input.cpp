#include <iostream>
#include <istream>
#include <fstream>
#include <input.h>
#include <data.h>
using namespace std;

class Input: public Model
{
public:
    void getBirdFile(vector<int> inpfiledata);
    void getCarFile(vector<int> inpcarfiledata);
};

void Input::getBirdFile(vector<int> inpfiledata)
{
    ifstream inpf("input_birds.txt");
    if(!inpf)
    {
        cout << "Error: file wasn't opened." << endl;
        return;
    }
    char *point[];
    while (inpf >> &point)
        inpfiledata.push_back(point);
    inpf.close();
    return;
}

void Input::getCarFile(vector<int> inpcarfiledata)
{
    ifstream inpcar("input_car.txt");
    if(!inpcar)
    {
        cout << "Error: file wasn't opened." << endl;
        return;
    }
    char *point[];
    while (inpcar >> &point)
        inpcarfiledata.push_back(point);
    inpcar.close();
    return;
}
