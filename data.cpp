#include "BASIC.h"
#include "data.h"


 vector<float> Data::weighs; // INIT??
 float Data::deltaTime=0.05f;
 vector<Creature*> Data::meadow;
 vector<Creature*> Data::pigeondata;
vector<vector<float> > Data::inpfile; // - координаты птиц
 Creature* Data::car;
vector<vector<float> > Data::carfile; // - координаты машин
 int Data::pointCount; 



Data::Data(){weighs.push_back(1.0); weighs.push_back(2.0); weighs.push_back(1.0);} //TODO: multipe init!

int Data::getPDataSize(){return pigeondata.size();}

Creature* Data::getPigeon(int pos) {return pigeondata[pos];}

void Data::setinpvec(Creature* v) { pigeondata.push_back(v);}

Creature* Data::getCar(){return car;}

void Data::setCar(Creature* c){car = c;}

vector<float> Data::getweights(){ return weighs; }

void Data::setinpfile(vector<float> v){inpfile.push_back(v);}

vector<float> Data::getinpfile(int pos){return inpfile[pos];}

int Data::getinpfilesize(){return inpfile.size();}

int Data::getcarfilesize(){return carfile.size();};

float Data::distance(vector<float> a, vector<float> b ){ return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2)); }

vector<float> Data::getCarPoint(int pos){ return carfile[pos];}

void Data::setcarfile(vector<float> v){ carfile.push_back(v); return;}

int Data::getpointCount(){return carfile.size();}

float Data::getdeltaTime(){return deltaTime;}

