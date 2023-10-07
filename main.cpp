#include "fieldb.h"
#include "model.h"
int main(int argc, char* argv[]){
  string fbirdname = argv[1];
  string fcarname = argv[2];
  FieldBehaviour fb;

  Model mod(&fb, fbirdname, fcarname);
  mod.simulate();
    return 0;
}