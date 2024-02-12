#include "fieldb.h"
#include "model.h"
int main(int argc, char* argv[]){
  if (argc != 2)
  {
    cout << "Error: incorrect number of arguments" << endl;
    return (-1);
  }
  string birdfilename = argv[1];
  FieldBehaviour fb;

  Model mod(&fb, birdfilename);
  mod.simulate();
  return 0;
}