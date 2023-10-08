
#ifndef BOIDS_COORD_H
#define BOIDS_COORD_H
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
};
#endif //BOIDS_COORD_H
