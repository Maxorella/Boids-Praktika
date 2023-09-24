#include "BASIC.h"
#include "Data.h"
#include "output.h"
void Output_F::createSlice()
{
    Data dat;
    static int i = 1;
    vector <float> v;
    ofstream outf(to_string(i));
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
    i++;
    return;
}
