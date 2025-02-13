#include "shapes.h"

#include "stdio.h"
#include <math.h>
int initializeSphere(SphereType* sphere, float x, float y, float z, float radius, int m){

    if(isnan(x) || isnan(y) || isnan(z) || isnan(radius)){
        printf("sphere coordinates are not a number\n");
        return -1;
    }
    sphere->x = x;
    sphere->y = y;
    sphere->z = z;
    sphere->radius = radius;
    sphere->m = m;

    sphere->r = 0.0;
    sphere->g = 0.0;
    sphere->b = 0.0;
    return 0;

}

int setColor(SphereType* sphere, float r, float g, float b){

    if(isnan(r) || isnan(g) || isnan(b)){
        printf("colors are not a number\n");
        return -1;
    }
    sphere->r = r;
    sphere->g = g;
    sphere->b = b;
    return 0;
}

void printSphere(SphereType *sphere){
    printf("sphere position: (x, y, z) = (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
    printf("sphere color: (r, g, b) = (%f, %f, %f)\n", sphere->r, sphere->g, sphere->b);
    printf("sphere radiues:  = %f\n", sphere->radius);
    printf("sphere tag:  = %d\n\n", sphere->m);

}
