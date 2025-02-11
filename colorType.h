#include "ray.h"
#include "shapes.h"
#include "vector.h"
typedef struct{
    float r, g, b;
} ColorType;

void initializeColorType(ColorType* color, float r, float g, float b);
/// @brief calculates the whether the ray intersects an object
/// @param ray a RayType containing the origin and the direction of the ray
/// @return returns the color obtained from the intersection or the background color
ColorType* traceRay(RayType *ray, SphereType* sphere, ColorType* backgroundColor);


/// @brief obtains the color of the shape if an intersection occurs
/// @param parameter for now it's the type of shape the intersection is.
/// @return returns the color obtained
ColorType shadeRay(char* parameter);

void printColor(ColorType* color);
