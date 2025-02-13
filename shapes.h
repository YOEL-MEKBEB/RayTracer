#ifndef SPHERETYPE
#define SPHERETYPE

typedef struct {
    float x, y, z;
    float radius;
    float r, g, b;
    int m;
} SphereType;

/// @brief initializes a new sphere given the parameter. sets the color to black
/// @param sphere a pointer to a sphere
/// @param x x coordinate of the center
/// @param y y coordinate of the center
/// @param z z coordinate of the center
/// @param radius radius of the sphere
/// @param m a tag used for identification and debugging
int initializeSphere(SphereType *sphere, float x, float y, float z, float radius, int m);

/// @brief sets the color of the sphere
/// @param sphere a pointer to a sphere
/// @param r the red color value
/// @param g the green color value
/// @param b the blue color value
int setColor(SphereType *sphere, float r, float g, float b);

/// @brief prints the attributes of the sphere to the console for debuggin
/// @param sphere a sphere pointer
void printSphere(SphereType *sphere);
#endif
