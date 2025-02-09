// #include "ray.h"
#include "vector.h"

/** todo: 
 * add view origin
 * add viewing direction vector
 * add up direction vector
 * add field of view
 * add horizontal fov
 * add vertical fov
 * define a viewing window
 * 
**/

typedef struct {
    // float viewOriginX, viewOriginY, viewOriginZ; // location of the camera
    Vector viewOrigin;

    // float upX, upY, upZ; // unit vector representing the up direction of camera
    Vector upVector; 

    //unit vector representing the direction where the camera is pointing
    Vector viewDirection;

    // viewing window
    Vector upperLeftCorner;
    Vector lowerLeftCorner;
    Vector upperRightCorner;
    Vector lowerRightCorner;
    // viewing window 
    float horizontalFOV; // in degrees
    float verticalFOV; // in degrees
    float aspectRatio;
    // storing w is not necessary since it's just -viewDirection;
    Vector u; // horizontal direction of the image. It's a normal vector
    Vector v; // vertical direction of the image. It's a normal vector

    

} Camera;

// initialize the cameras position
void initialize_camera(Camera *camera, float viewOriginX, float viewOriginY, float viewOriginZ);

// set up it's upvector
void setUpVector(Camera *camera, float upX, float upY, float upZ);

//set up the viewing direction of the vector
void setViewingDirection(Camera *camera, float viewDirectionX, float viewDirectionY, float viewDirectionZ);

// set the horizontal field of view in degrees
void setHorizontalFOV(Camera* camera, float horizontalFOV);

// set the vertical field of view in degrees
void setVericalFOV(Camera* camera, float verticalFOV);

// calculates the values of u and v given that the view direction
// and the up vector
void defineImageCoordinates(Camera* camera);

// set the aspect ratio of the image
void setAspectRatio(Camera* camera, float width, float height);

// create a viewing window for shooting rays.
void setViewingWindow(Camera* camera, float d);

//print the contents of the camera for debugging
void printCamera(Camera* camera);


