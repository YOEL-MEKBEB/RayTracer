#include "ray.h"
#include "stdlib.h"

void initializeRayType(RayType *ray, float x, float y, float z, float bgIndexOfrefraction){
    ray->x = x;
    ray->y = y;
    ray->z = z;

    ray->dx = 0.0;
    ray->dy = 0.0;
    ray->dz = 0.0;
    
    ray->bgIndexOfrefraction = bgIndexOfrefraction;
    ray->currentIndeOfRefraction = bgIndexOfrefraction;
    ray->isInsideObject = 0;
    ray->indexOfSphere = -1;
    ray->indexOfTriangle = -1;
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

void setSphereIndex(RayType *ray, float index){
    ray->indexOfSphere = index;
}


void setRayCurrentIdxOfRefraction(RayType *ray, float curIdxOfRefraction){
    ray->currentIndeOfRefraction = curIdxOfRefraction;
}

void setIsInsideObject(RayType *ray, short isInsideObject){
    ray->isInsideObject = isInsideObject;
}
void printRay(RayType *ray){
    printf("(x, y, z) = (%f, %f, %f)\n", ray->x, ray->y, ray->z);
    printf("(dx, dy, dz) = (%f, %f, %f)\n", ray->dx, ray->dy, ray->dz);
    printf("bgIndexOfRefraction = %f\n", ray->bgIndexOfrefraction);
    printf("current index of refraction = %f\n", ray->currentIndeOfRefraction);
    printf("index of sphere  = %f\n", ray->indexOfSphere);
    printf("index of triangle = %f\n", ray->indexOfTriangle);
    printf("is inside object = %d\n\n", ray->isInsideObject);
    
}
