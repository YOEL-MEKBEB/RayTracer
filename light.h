#ifndef LIGHT
#define LIGHT
#include "vector.h"

typedef struct{
  Vector lightLocation;
  int isPoint;
  float lightIntensity;
} Light;



int setLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity);
#endif
