#ifndef RAYTYPE
#define RAYTYPE

#include <math.h>
#include <stdio.h>

// if x, y, z = 0 then the array is starting from the origin
typedef struct {
    float x, y, z;
    float dx, dy, dz;
    float r, g, b;
} RayType;


void initializeRayType(RayType *ray, int dx, int dy, int dz);


// returns the dot product between the 2 rays
float rayDotProduct(RayType *ray1, RayType *ray2);

// returns the cross product between ray1 x ray2
// assumes that ray1 and ray2 are at the origin
RayType* rayCrossProduct(RayType *ray1, RayType *ray2);

// returns the sum of the 2 rays 
RayType* RaySum(RayType *ray1, RayType *ray2);

// multiplies the scalar value provided with the ray and returns the new vector
RayType* scalarRayMult(float scalar, RayType *ray);

// calculates the magnitude of the ray
float Raylength(RayType *ray);

int recordColor(RayType *ray, float r, float g, float b);

// print the ray in the console for debugging
void printRay(RayType *ray);
#endif

