#include "BASIC.h"
#include "ALL.h"


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
