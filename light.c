#include "light.h"

 int setLightParameters(Light *light, float lightX, float lightY, float lightZ, int isPoint, float lightIntensity){
    Vector lightLocation;
    initialize_vector(&lightLocation, lightX, lightY, lightZ);
    light->lightLocation = lightLocation;
    light->isPoint = isPoint;
    light->lightIntensity = lightIntensity;
    return 0;
}
