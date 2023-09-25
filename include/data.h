#ifndef Datah
#define Datah

#include "BASIC.h"
#include "creature.h"
class Data
{
private:

    static vector<float> weighs; // INIT??
    static float deltaTime;
    static vector<Creature*> meadow;
    static vector<Creature*> pigeondata;
    static Creature* car;
    static vector<vector<float> > inpfile; // - координаты птиц
    static vector<vector<float> > carfile; // - координаты машин
    static int pointCount; 
    //static vector<vector<float> > outfile;
public:
    Data();
    int getinpfilesize();
    int getcarfilesize();

    int getPDataSize();

    Creature* getPigeon(int);

    void setinpvec(Creature*);

    Creature* getCar();

    void setCar(Creature*);

    vector<float> getweights();

    void setinpfile(vector<float> v);

    vector<float> getinpfile(int pos);

    float distance(vector<float> a, vector<float> b );

    vector<float> getCarPoint(int pos);

    void setcarfile(vector<float> v);

    int getpointCount();

    float getdeltaTime();
    
  
    ~Data(){};
};

#endif
