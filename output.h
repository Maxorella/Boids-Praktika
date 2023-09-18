#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <data.h>
using namespace std;

class output:public Model
{
public:
    void createSlice(vector<int> outfiledata);
};
