#ifndef RAYTYPE
#define RAYTYPE

#include <math.h>
#include <stdio.h>

// if x, y, z = 0 then the array is starting from the origin
typedef struct {
    float x, y, z;
    float dx, dy, dz;
    short indexOfSphere;
    short indexOfTriangle;
    float bgIndexOfrefraction;
    float currentIndeOfRefraction;
    short isInsideObject;
    short isbackgroundcolored;
    
} RayType;

//initializes the position of the ray
void initializeRayType(RayType *ray, float x, float y, float z, float bgIndexOfRefraction);

// sets the direction of the ray
void setDirection(RayType *ray, float dx, float dy, float dz);

// returns the sum of the 2 rays 
// RayType* RaySum(RayType *ray1, RayType *ray2);

// multiplies the scalar value provided with the ray and returns the new vector
RayType* scalarRayMult(float scalar, RayType *ray);

// calculates the magnitude of the ray
float Raylength(RayType *ray);

void setSphereIndex(RayType *ray, float index);

void setRayCurrentIdxOfRefraction(RayType *ray, float curIdxOfRefraction);

void setIsInsideObject(RayType *ray, short isInsideObject);

// print the ray in the console for debugging
void printRay(RayType *ray);
#endif

