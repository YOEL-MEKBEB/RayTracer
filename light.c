#include "light.h"
#include "vector.h"

 int setLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity){
    Vector lightLocation;
    if(initialize_vector(&lightLocation, lightX, lightY, lightZ) == -1){
      printf("failed in setLightParameters");
    }
    light->lightLocation = lightLocation;
    light->isPoint = isPoint;
    light->lightIntensity = lightIntensity;
    light->c1 = 0.0;
    light->c2 = 0.0;
    light->c3 = 0.0;
    light->isAttenuated = 0;
    return 0;
}

int setAttLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity, float c1, float c2, float c3){
  
    Vector lightLocation;
    if(initialize_vector(&lightLocation, lightX, lightY, lightZ) == -1){
      printf("failed in setAttLightParameters");
    }
    light->lightLocation = lightLocation;
    light->isPoint = isPoint;
    light->c1 = c1;
    light->c2 = c2;
    light->c3 = c3;
    light->lightIntensity = lightIntensity;
    light->isAttenuated = 1;
    return 0;
}

void printLight(Light *light){
  printf("light location: ");
  printVector(&light->lightLocation);
  printf("light intensity: %f\n",  light->lightIntensity);
  printf("light c1, c2, c3: %f, %f, %f\n", light->c1, light->c2, light->c3);
}
