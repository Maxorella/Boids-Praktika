#include <iostream>
#include <istream>
#include <fstream>
#include <output.h>
#include <data.h>

class output:public Model
{
public:
    void createSlice(vector<int> outfiledata);
};



void output::createSlice(vector<int> outfiledata)
{
    static int i = 1;
    ofstream outf("%d.txt", i);
    if(!outf)
    {
        cout << "Error: file wasn't created." << endl;
        return;
    }
    for ( int i = 0 ; i < temp2d.size() ; i++ ) 
    {
        copy(temp2d.at(i).begin(), temp2d.at(i).end(), outfiledata);
        outf << '\n';
    }
    outf.close();
    return;
}
