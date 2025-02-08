#include "shapes.h"

void initializeSphere(SphereType* sphere, float x, float y, float z, float radius){
    sphere->x = x;
    sphere->y = y;
    sphere->z = z;
    sphere->radius = radius;

    sphere->r = 0.0;
    sphere->g = 0.0;
    sphere->b = 0.0;

}

void setColor(SphereType* sphere, float r, float g, float b){
    sphere->r = r;
    sphere->g = g;
    sphere->b = b;
}