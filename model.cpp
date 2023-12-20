#include <iostream>
#include <vector>
#include "pigeon.h"
#include "fieldb.h"
#include "car.h"
#include "model.h"
#include "input.h"
#include "food.h"
#include "obstacle.h"

using namespace std;
Model::Model(FieldBehaviour* b, string bfile, string cfile): behavController(b), birdFileName(bfile), carFileName(cfile){ // работает
    InputController inputControl;
   // inputControl.getBirdFile(birdFileName);
   // inputControl.getCarFile(carFileName);
    inputControl.ReadInputFile(birdFileName);
    //cout<< endl<< "Ending" << endl;
    for (int i =0; i<dat.getPigeonsCount(); i++){
        //cout << dat.getPigStartPos(i).x << dat.getPigStartPos(i).y << dat.getPigStartPos(i).z << endl;
        Pigeon* pigeon =  new Pigeon(dat.getPigStartPos(i),b);
        dat.setPigToMeadow(pigeon);
    }
    //cout << dat.getCarPoint(0).x << dat.getCarPoint(0).y << dat.getCarPoint(0).z << endl;

    Car* carr = new Car(dat.getCarPoint(0));
    dat.setCar(carr);


    for (int i =0; i<dat.GetStartFoodCount(); i++){
      //  cout << dat.getPigStartPos(i).x << dat.getPigStartPos(i).y << dat.getPigStartPos(i).z << endl;
        Food* food =  new Food(dat.GetFoodStart(i), b);
        dat.SetFood(food);
    }

    for (int i =0; i<dat.getObstCount(); i++){
        //  cout << dat.getPigStartPos(i).x << dat.getPigStartPos(i).y << dat.getPigStartPos(i).z << endl;
        Obstacle* obst =  new Obstacle(dat.getObstStartPos(i), b);
        dat.setObst(obst);
    }



}


void Model::simulate(){
    for(int j=0; j<4000; j++){
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
