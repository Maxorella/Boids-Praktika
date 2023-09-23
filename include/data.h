#ifndef Datah
#define Datah

#include "ALL.h"
#include "BASIC.h"


class Data
{
private:

    static vector<float> weighs; // INIT??
    static inline float deltaTime=0.05f;
    static vector<Creature*> meadow;
    static vector<Creature*> pigeondata;
    static Creature* car;
    static vector<vector<float> > inpfile; // - координаты птиц
    static vector<vector<float> > carfile;
    static int pointCount; 
    //static vector<vector<float> > outfile;
    
   // static vector<float>
public:
    Data(){weighs.push_back(1.0); weighs.push_back(2.0); weighs.push_back(1.0);}
    int getPDataSize(){return pigeondata.size();}
    Creature* getPigeon(int pos) {return pigeondata[pos];}
    void setinpvec(Creature* v) { pigeondata.push_back(v);}
    Creature* getCar(){return car;}
    void setCar(Creature* c){car = c;}
    vector<float> getweights(){ return weighs; }
    void setinpfile(vector<float> v){inpfile.push_back(v);}
    vector<float> getinpfile(int pos){return inpfile[pos];}

    float distance(vector<float> a, vector<float> b ){ return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2)); }
    vector<float> getCarPoint(int pos){ return carfile[pos];}
    int getpointCount(){return pointCount;}
    float getdeltaTime(){return deltaTime;}
  
    ~Data();
};

#endif
