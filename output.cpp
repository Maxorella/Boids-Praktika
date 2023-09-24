#include "BASIC.h"
#include "ALL.h"

void Output_F::createSlice()
{
    Data dat;
    static int i = 1;
    vector <float> v;
    ofstream outf("%d.txt", i);
    if(!outf.is_open())
    {
        cout << "Error: file wasn't created." << endl;
        return;
    }
    for ( int j = 0 ; j < dat.getPDataSize(); j++ ) 
    {
        for (float g: dat.getPigeon(j)->getpos())
            outf << g << " ";
        outf << std::endl;
    }
    outf.close();
    return;
}
