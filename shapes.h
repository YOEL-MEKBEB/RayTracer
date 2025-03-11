#ifndef SPHERETYPE
#define SPHERETYPE

#include "vector.h"
typedef struct {
    float x, y, z;          // center of sphere
    float radius;           // radius of sphere
    float Odr, Odg, Odb;    // intrinsic color
    float Osr, Osg, Osb;    // specular color
    float ka, kd, ks;       // ambient, diffuse, and specular weights
    int shinyFactor;        // the value that controls the density of the specular term
    int useTexture;         // determines which texture to use the list of textures and serves as a
                            // boolean at the same time
    int m;                  // index of sphere in sphere array

} SphereType;

/// @brief initializes a new sphere given the parameter. sets the color to black
/// @param sphere a pointer to a sphere
/// @param x x coordinate of the center
/// @param y y coordinate of the center
/// @param z z coordinate of the center
/// @param radius radius of the sphere
/// @param m a tag used for identification and debugging
int initializeSphere(SphereType *sphere, float x, float y, float z, float radius, int m,
                     int useTexture);

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
typedef struct {
    Vector face;            // indices of the vertices
    Vector normal;          // indices of the normals
    Vector texture;         // indices of the texture coordinates
    float Odr, Odg, Odb;    // intrinsic colors
    float Osr, Osg, Osb;    // specular colors
    float ka, kd, ks;       // ambient, diffuse, and specular weights
    int shinyFactor;        // the value that determines the density of the specular term
    int isSmoothShaded;     // boolean to check whether to use vertex normals or not
    int useTexture;         // determines which texture to use the list of textures and serves as a
                            // boolean at the same time
} Triangle;

/// @brief initializes triangle
/// @param triangle
/// @param v1 vertex 1
/// @param v2 vertex 2
/// @param v3 vertex 3
/// @param isSmooth boolean to determine whether it's smooth shaded
/// @param useTexture index of the texture in the texture list to be used
/// @return returns 0 on success and -1 on failure
int initializeTriangle(Triangle *triangle, float v1, float v2, float v3, int isSmooth,
                       int useTexture);

/// @brief sets the triangle normals indices
/// @param triangle
/// @param n1 normal index 1
/// @param n2 normal index 2
/// @param n3 normal index 3
/// @return returns 0 on success and -1 on failure
int setTriangleNormal(Triangle *triangle, float n1, float n2, float n3);

/// @brief sets the triangle texture indices
/// @param triangle
/// @param t1 texture index 1
/// @param t2 texture index 2
/// @param t3 texture index 3
/// @return returns 0 on success and -1 on failure
int setTriangleTexture(Triangle *triangle, float t1, float t2, float t3);

/// @brief sets the intrinsic color of the triangle
/// @param triangle
/// @param r red component
/// @param g green component
/// @param b blue component
/// @return returns 0 on success and -1 on failure
int setIntrinsicTriangle(Triangle *triangle, float r, float g, float b);

/// @brief sets the specular color of the triangle
/// @param triangle
/// @param r red component
/// @param g green component
/// @param b blue component
/// @return returns 0 on success and -1 on failure
int setSpecularTriangle(Triangle *triangle, float r, float g, float b);

/// @brief sets the weight of the ambient term, diffuse term, specular term
/// @param triangle
/// @param ka ambient weight
/// @param kd diffuse weight
/// @param ks specular weight
/// @return returns 0 on success and -1 on failure
int setTriangleWeight(Triangle *triangle, float ka, float kd, float ks);

/// @brief assigns the shiny factor
/// @param triangle
/// @param shinyFactor
/// @return returns 0 on success and -1 on failure
int setTriangleShinyFactor(Triangle *triangle, int shinyFactor);

/// @brief prints the triangles info for debugging
/// @param triangle
void printTriangle(Triangle *triangle);

#endif
