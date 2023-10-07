#include <iostream>
#include <vector>
#include "pigeon.h"
#include "fieldb.h"
#include "car.h"
#include "model.h"
#include "input.h"
using namespace std;
Model::Model(FieldBehaviour* b, string bfile, string cfile): beh(b), birdfilename(bfile), carfilename(cfile){
    Input_F inpp;
    inpp.getBirdFile(birdfilename);
    inpp.getCarFile(carfilename);
    for (int i =0; i<dat.getinpfilesize(); i++){
        Pigeon* pig =  new Pigeon(dat.getinpfile(i),b);
        dat.setinpvec(pig);
    }

        Car* carr = new Car(dat.getCarPoint(0));
        dat.setCar(carr);
}


void Model::simulate(){
    for(int j=0; j<2000; j++){
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
