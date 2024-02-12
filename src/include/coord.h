
#ifndef BOIDS_COORD_H
#define BOIDS_COORD_H
#include <cmath>
struct Vec3Cord{
    float x;
    float y;
    float z;
    Vec3Cord():x(0),y(0),z(0){}
    Vec3Cord(float xx, float yy, float zz):x(xx), y(yy), z(zz){}
    Vec3Cord(const Vec3Cord &p){
        x=p.x;
        y=p.y;
        z=p.z;
    }
   // float GetLength(){return sqrt(x*x+y*y+z*z);}
};


struct Vec4Cord{
    float x;
    float y;
    float z;
    float r;
    Vec4Cord():x(0),y(0),z(0), r(0){}
    Vec4Cord(float xx, float yy, float zz, float rr):x(xx), y(yy), z(zz), r(rr){}
    Vec4Cord(const Vec4Cord &p){
        x=p.x;
        y=p.y;
        z=p.z;
        r=p.r;
    }
    // float GetLength(){return sqrt(x*x+y*y+z*z);}
};

#endif //BOIDS_COORD_H
