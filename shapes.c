#include "shapes.h"

#include "stdio.h"
void initializeSphere(SphereType* sphere, float x, float y, float z, float radius, int m){
    sphere->x = x;
    sphere->y = y;
    sphere->z = z;
    sphere->radius = radius;
    sphere->m = m;

    sphere->r = 0.0;
    sphere->g = 0.0;
    sphere->b = 0.0;

}

void setColor(SphereType* sphere, float r, float g, float b){
    sphere->r = r;
    sphere->g = g;
    sphere->b = b;
    printf("setColor: (%f, %f, %f)\n", r, g, b);
    printf("setColor2: (%f, %f, %f)\n", sphere->r,sphere-> g, sphere->b);
}

void printSphere(SphereType *sphere){
    printf("sphere position: (x, y, z) = (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
    printf("sphere color: (r, g, b) = (%f, %f, %f)\n", sphere->r, sphere->g, sphere->b);
    printf("sphere radiues:  = %f\n", sphere->radius);
    printf("sphere tag:  = %d\n\n", sphere->m);

}