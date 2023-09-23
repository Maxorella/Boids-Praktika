#ifndef Modelh
    #define Modelh

#include "ALL.h"
#include "BASIC.h"

class Model{
private:
    Output outobj;
    float timer=0;
    float sliceTime=40;
    Data dat;
    FieldBehaviour* beh;
public:
    Model(FieldBehaviour* b);
    void simulate();
    ~Model();
};



Model::Model(FieldBehaviour* b): beh(b){

    // 
}


void Model::simulate(){
    for(int j=0; j<1000; j++){
        beh->allBehave();
        beh->allMove();
        timer+=1;
        if (timer>=sliceTime){
            timer-=sliceTime;
            outobj.createSlice();
        }
    }
    
}
Model::~Model()
{
}

#endif
