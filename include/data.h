#ifndef Datah
#define Datah

#include "BASIC.h"
class Creature;

class Data
{
private:

    static vector<float> weighs; // INIT??
    static inline float deltaTime=0.05f;
    static vector<Creature*> meadow;
    static vector<Creature*> pigeondata;
    static Creature* car;
    static vector<vector<float> > inpfile; // - координаты птиц
    static vector<vector<float> > carfile; // - координаты машин
    static int pointCount; 
    //static vector<vector<float> > outfile;
    
   // static vector<float>
public:
    Data();

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

    vector<float> setcarfile(vector<float> v);

    int getpointCount();

    float getdeltaTime();
    
  
    ~Data();
};

#endif
