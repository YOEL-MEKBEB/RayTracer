#include "ray.h"
#include "shapes.h"
#include "vector.h"
#include "light.h"
typedef struct {
    float r, g, b;
} ColorType;

void initializeColorType(ColorType *color, float r, float g, float b);
/// @brief calculates the whether the ray intersects an object
/// @param ray a RayType containing the origin and the direction of the ray
/// @return returns the color obtained from the intersection or the background color. returns a
/// color with values of -1 to indicate error
ColorType traceRay(RayType *ray, SphereType **sphereArray, int sizeOfArray,
                   ColorType *backgroundColor, Light* light);


/// @brief obtains the color of the shape if an intersection occurs
/// @param parameter for now it's the type of shape the intersection is.
/// @return returns the color obtained
//
/* for assignment 1a, we only need to pass in an
identifier that allows access to the material
properties of the intersected object; in the future,
we will need to also provide the coordinates of the
point where the shading will be computed */

ColorType shadeRay(char* objectType, SphereType* sphere, RayType *ray,  Vector *surfacePoint,  Light* light, SphereType** sphereArray, int sizeOfArray);

/// @brief prints the attributes of the color for debugging
/// @param color
void printColor(ColorType *color);
