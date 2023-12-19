#include "fieldb.h"
#include "model.h"
int main(int argc, char* argv[]){
  if (argc != 3)
  {
    cout << "Error: incorrect number of arguments" << endl;
    return (-1);
  }
  string birdfilename = argv[1];
  string carfilename = argv[2];
  FieldBehaviour fb;

  Model mod(&fb, birdfilename, carfilename);
  mod.simulate();
  return 0;
}