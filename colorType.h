#include "ray.h"
#include "shapes.h"
#include "vecList.h"
#include "vector.h"
#include "light.h"
typedef struct {
    float r, g, b;
} ColorType;

void initializeColorType(ColorType *color, float r, float g, float b);

/// @brief calculates the whether the ray intersects an object and calls shadeRay to color the pixel
/// @param ray a RayType containing the origin and the direction of the ray
/// @param sphereArray an array of sphere pointers to iterate through and check intersection of rays
/// @param sizeOfArray size of the sphereArray
/// @param backgroundColor 
/// @param light light object for coloring
/// @return returns the color obtained from the intersection or the background color. returns a
/// color with values of -1 to indicate error

ColorType traceRay(RayType *ray, SphereType **sphereArray, int sizeOfArray,
                   ColorType *backgroundColor, Light** light, int numberOfLights, vec_list *vertices, tri_list *faces, vec_list *normals, tex_list *textures);


/// @brief colors the ray of with the closest object of intersection
/// @param objectType identifier of the object //will be used later when I add more shapes
/// @param sphere the sphere that is to be colored
/// @param ray the ray that intersected the sphere
/// @param surfacePoint the location of the intersection
/// @param light light object for coloring
/// @param sphereArray an array of sphere to check for occurence of shadows
/// @param sizeOfArray size of sphereArray
/// @return 
ColorType shadeRay(char* objectType, SphereType* sphere, Triangle *triangle, RayType *ray,
                   Vector *surfacePoint,  Light** light, int numberOfLights, SphereType** sphereArray, int sizeOfArray, Vector *normalCoord, vec_list* normals, tex_list *textures);


ColorType shadeTriangle(Triangle *triangle, RayType *ray, Vector *surfacePoint, Light** lightArray, int numberOfLights, Vector *normalCoord, vec_list* normals);
/// @brief prints the attributes of the color for debugging
/// @param color
void printColor(ColorType *color);
