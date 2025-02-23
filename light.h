#ifndef LIGHT
#define LIGHT
#include "vector.h"

typedef struct{
  Vector lightLocation; // location of point source light, or vector for a directional light
  int isPoint; //identifier to check if it's a point source light or a direcional light
  float lightIntensity; // the intensity of the light
  float c1, c2, c3; // scalar values used for light source attenuation. set to 0.0 if isAttenuated is 0
  int isAttenuated; // identifier to check whether the light is attenuated or not
} Light;

/// @brief sets the light parameters for a non attenuated light
/// @param light light pointer
/// @param lightX x location or x component of vector
/// @param lightY y location or y component of vector
/// @param lightZ z location or z component of vector
/// @param isPoint determines whether light is point source light or direction light
/// @param lightIntensity intensity of light
/// @return 0 on success, -1 on failure
int setLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity);

/// @brief sets the light parameters for an attenuated light
/// @param light light pointer
/// @param lightX x location or x component of vector
/// @param lightY y location or y component of vector
/// @param lightZ z location or z component of vector
/// @param isPoint determines whether light is point source light or direction light
/// @param lightIntensity intensity of light
/// @param c1 scalar value for attenuation calculation
/// @param c2 scalar value for attenuation calculation
/// @param c3 scalar value for attenuation calculation
/// @return 0 on success, -1 on failure
int setAttLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity, float c1, float c2, float c3);

/// @brief prints the light parameters for debuggin
/// @param light light pointer
void printLight(Light *light);

#endif
