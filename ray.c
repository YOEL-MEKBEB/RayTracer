#include "ray.h"
#include "stdlib.h"

void initializeRayType(RayType *ray, float x, float y, float z){
    ray->x = x;
    ray->y = y;
    ray->z = z;

    ray->dx = 0.0;
    ray->dy = 0.0;
    ray->dz = 0.0;

}


void setDirection(RayType *ray, float dx, float dy, float dz){
    ray->dx = dx;
    ray->dy = dy;
    ray->dz = dz;
}

// RayType* RaySum(RayType *ray1, RayType *ray2){
//     RayType* sum = malloc(sizeof(RayType));
//     sum->x = ray1->x;
//     sum->y = ray1->y;
//     sum->z = ray1->z;

//     sum->dx = ray1->dx + ray2->dx;
//     sum->dy = ray1->dy + ray2->dy;
//     sum->dz = ray1->dz + ray2->dz;

//     return sum;
// }

RayType* scalarRayMult(float scalar, RayType *ray){
    RayType* result = ray;
    result->dx = scalar * ray->dx;
    result->dy = scalar * ray->dy;
    result->dz = scalar * ray->dz;

    return result;
}

float Raylength(RayType *ray){
    return sqrt(pow(ray->dx, 2) + pow(ray->dy, 2) + pow(ray->dz, 2));
}

int recordColor(RayType *ray, float r, float g, float b){
    if(r > 1 || g > 1 || b > 1){
        printf("the r, g, or b value of the color is greater than one\n please normalize it.");
        return -1;
    }
    ray->r = r;
    ray->g = g;
    ray->b = b;
    return 0;
}

void printRay(RayType *ray){
    printf("(x, y, z) = (%f, %f, %f)\n", ray->x, ray->y, ray->z);
    printf("(dx, dy, dz) = (%f, %f, %f)\n\n", ray->dx, ray->dy, ray->dz);
}
