class Data;

#include <fieldb.h>
class Model{
private:
    float timer=0;
    float sliceTime=40;
    Data dat;
    FieldBehaviour* beh;
public:
    Model(FieldBehaviour* b);
    void simulate();
    ~Model();
};



Model::Model(FieldBehaviour* b): beh(b){}


void Model::simulate(){
    beh->allBehave();
    beh->allMove();
    timer+=1;
    if (timer>=sliceTime){
        timer-=sliceTime;
        // call slice
    }
}
Model::~Model()
{
}