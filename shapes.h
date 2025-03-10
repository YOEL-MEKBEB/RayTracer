#ifndef SPHERETYPE
#define SPHERETYPE

#include "vector.h"
typedef struct {
    float x, y, z;
    float radius;
    float Odr, Odg, Odb;
    float Osr, Osg, Osb;
    float ka, kd, ks;
    int shinyFactor;
    int useTexture;
    int m;
    
} SphereType;

/// @brief initializes a new sphere given the parameter. sets the color to black
/// @param sphere a pointer to a sphere
/// @param x x coordinate of the center
/// @param y y coordinate of the center
/// @param z z coordinate of the center
/// @param radius radius of the sphere
/// @param m a tag used for identification and debugging
int initializeSphere(SphereType *sphere, float x, float y, float z, float radius, int m, int useTexture);

/// @brief sets the color of the sphere
/// @param sphere a pointer to a sphere
/// @param r the red color value
/// @param g the green color value
/// @param b the blue color value
int setIntrinsicColor(SphereType *sphere, float r, float g, float b);

int setSpecularColor(SphereType *sphere, float r, float g, float b);
int setWeight(SphereType *sphere, float ka, float kd, float ks);
int setShinyFactor(SphereType *sphere, int shinyFactor);

// int setTexture(SphereType *sphere, vec_list **texture);

/// @brief prints the attributes of the sphere to the console for debuggin
/// @param sphere a sphere pointer
void printSphere(SphereType *sphere);
#endif

#ifndef TRIANGLE
#define TRIANGLE
typedef struct{
    Vector face;
    Vector normal;
    float Odr, Odg, Odb;
    float Osr, Osg, Osb;
    float ka, kd, ks;
    int shinyFactor;
    int isSmoothShaded;
} Triangle;

int initializeTriangle(Triangle *triangle, float v1, float v2, float v3, int isSmooth);

int setTriangleNormal(Triangle *triangle, float n1, float n2, float n3);

int setIntrinsicTriangle(Triangle *triangle, float r, float g, float b);

int setSpecularTriangle(Triangle *triangle, float r, float g, float b);

int setTriangleWeight(Triangle *triangle, float ka, float kd, float ks);

int setTriangleShinyFactor(Triangle *triangle, int shinyFactor);

void printTriangle(Triangle *triangle);

#endif
