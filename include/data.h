#ifndef Datah
#define Datah

#include <vector>
#include <iostream>
#include "creature.h"
#include "coord.h"
using namespace std;

class Data
{
private:

    static vector<float> weighs; // INIT??
    static float timeMultiplier;
   // static vector<Creature*> meadow;
    static vector<Creature*> pigeonsInMeadow;
    static Creature* car;
    static vector<Vec3Cord> startPigeonsPoses; // - координаты птиц
    static vector<Vec3Cord> startFoodPoses;
    static vector<Vec3Cord> carPosesInstruction; // - координаты машин
    static vector<Vec4Cord> startObstPoses; // - иниц коорд препятств
    static vector<Creature*> FoodInMeadow;
    static vector<Creature*> obstacles; // - позиции препятствий
   // static int pointCount;
    //static vector<vector<float> > outfile;
public:
    Data();
    int getPigeonsCount();
   // int getcarfilesize();

    int getPigInMeadowSize();

    Creature* getPigeon(int);

    void setPigToMeadow(Creature*);

    Creature* getCar();

    void setCar(Creature*);

   // vector<float> getweights();

    void setPigStartPos(Vec3Cord v);

    Vec3Cord getPigStartPos(int pos);

    float distance(Vec3Cord vec3a, Vec3Cord vec3b);
    float distance2d(Vec3Cord vec3a, Vec3Cord vec3b );

    Vec3Cord getCarPoint(int pos);

    void setCarPoint(Vec3Cord v);

    int getCarPointCount();

    float getTimeMultpl();

    void AddFoodStart(Vec3Cord v);

    void SetFood(Creature* v);

    int GetFoodCount();
    int GetStartFoodCount();
    Vec3Cord GetFoodStart(int pos);

    Creature* GetFoodPos(int pos);

    bool RemoveFood(Creature* ptr);


    void setObstStartPos(Vec4Cord);
    Vec4Cord getObstStartPos(int);

    Creature* getObst(int);
    void setObst(Creature*);

    int getObstCount();

    Vec4Cord getObstStartPos();

    ~Data(){};
};

#endif
