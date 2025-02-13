// #include "ray.h"
#include "vector.h"

/// @brief a struct to define the camera in the scene. Contains viewing window as well
typedef struct {
    // float viewOriginX, viewOriginY, viewOriginZ; // location of the camera
    Vector viewOrigin;

    // unit vector representing the up direction of camera
    Vector upVector;

    // unit vector representing the direction where the camera is pointing
    Vector viewDirection;

    // viewing window
    Vector upperLeftCorner;
    Vector lowerLeftCorner;
    Vector upperRightCorner;
    Vector lowerRightCorner;
    // viewing window
    //
    float horizontalFOV;    // in degrees
    float verticalFOV;      // in degrees
    float aspectRatio;      // the aspect ratio of the image to be created

    // storing w is not necessary since it's just -viewDirection;
    Vector u;    // horizontal direction of the image. It's a normal vector
    Vector v;    // vertical direction of the image. It's a normal vector

} Camera;

/// @brief initialize the cameras position
/// @param camera a camera pointer
/// @param viewOriginX x location of the camera
/// @param viewOriginY y location of the camera
/// @param viewOriginZ z location of the camera
int initialize_camera(Camera *camera, float viewOriginX, float viewOriginY, float viewOriginZ);

/// @brief set up the up vector as long as it's not a 0 vector
/// @param camera a camera pointer
/// @param upX
/// @param upY
/// @param upZ
/// @return returns 0 on success, returns -1 if a 0 vector is provided
int setUpVector(Camera *camera, float upX, float upY, float upZ);

/// @brief  set up the viewing direction of the vector
/// @param camera
/// @param viewDirectionX
/// @param viewDirectionY
/// @param viewDirectionZ
/// @return returns 0 on success, returns -1 if a 0 vector is provided
int setViewingDirection(Camera *camera, float viewDirectionX, float viewDirectionY,
                        float viewDirectionZ);

/// @brief set the horizontal field of view in degrees
/// @param camera
/// @param horizontalFOV
int setHorizontalFOV(Camera *camera, float horizontalFOV);

/// @brief  set the vertical field of view in degrees
/// @param camera
/// @param verticalFOV
int setVericalFOV(Camera *camera, float verticalFOV);

/// @brief calculates the values of u and v given that the view direction
// and the up vector are provided
/// @param camera
void defineImageCoordinates(Camera *camera);

/// @brief set the aspect ratio of the image
/// @param camera
/// @param width
/// @param height
int setAspectRatio(Camera *camera, float width, float height);

/// @brief create a viewing window for shooting rays.
/// @param camera
/// @param d
void setViewingWindow(Camera *camera, float d);

/// @brief print the contents of the camera for debugging
/// @param camera
void printCamera(Camera *camera);
