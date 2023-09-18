#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <data.h>
using namespace std;

class Input: public Model
{
public:
    void getBirdFile(vector<int> inpfiledata);
    void getCarFile(vector<int> inpcarfiledata);
};
