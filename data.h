#include <iostream>
#include <creature.h>
#include <vector>

class Creature;
using namespace std;

class Data
{
private:
    static vector<Creature*> meadow();
    static inline vector<float> weights{1, 2, 3};
    static vector<Creature*> pigeondata;
    static Creature* car;
    static vector<vector<float>> inpfile; // - координаты птиц
    //static vector<vector<float>> carfile;
    static vector<vector<float> > outfile;
    
   // static vector<float>
public:
    int getPDataSize(){return pigeondata.size();}
    Creature* getPigeon(int pos) {return pigeondata[pos];}
    void setinpvec(Creature* v) { pigeondata.push_back(v);}
    Creature* getCar(){return car;}
    void setCar(Creature* c){car = c;}
    vector<float> getweights(){return weights;}
    void setinpfile(vector<float> v){inpfile.push_back(v);}
    vector<float> getinpfile(int pos){return inpfile[pos];}
    Data();
    ~Data();
};
