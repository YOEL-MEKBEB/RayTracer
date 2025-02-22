#ifndef LIGHT
#define LIGHT
#include "vector.h"

typedef struct{
  Vector lightLocation;
  int isPoint;
  float lightIntensity;
  float c1, c2, c3;
  int isAttenuated;
} Light;


int setLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity);


int setAttLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity, float c1, float c2, float c3);

void printLight(Light *light);

#endif
