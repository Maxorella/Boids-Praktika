
#include <data.h>
#include <model.h>

Model::Model()
{

 Data dat;
 }
void Model::simulate(){
    
    timer+=1;
    if (timer>=sliceTime){
        timer-=sliceTime;
        // call slice
    }
}
Model::~Model()
{
}