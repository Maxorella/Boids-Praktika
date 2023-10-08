#include <iostream>
#include <vector>
#include "pigeon.h"
#include "fieldb.h"
#include "car.h"
#include "model.h"
#include "input.h"
using namespace std;
Model::Model(FieldBehaviour* b, string bfile, string cfile): behavController(b), birdFileName(bfile), carFileName(cfile){
    InputController inputControl;
    inputControl.getBirdFile(birdFileName);
    inputControl.getCarFile(carFileName);
    for (int i =0; i<dat.getPigeonsCount(); i++){
        Pigeon* pigeon =  new Pigeon(dat.getPigStartPos(i),b);
        dat.setPigToMeadow(pigeon);
    }

        Car* carr = new Car(dat.getCarPoint(0));
        dat.setCar(carr);
}


void Model::simulate(){
    for(int j=0; j<2000; j++){
        behavController->allBehave();
        behavController->allMove();
        timer+=1;
        if (timer>=sliceTime){
            timer-=sliceTime;
            outController.createSlice();
        }
    }
    
}
Model::~Model()
{
}
