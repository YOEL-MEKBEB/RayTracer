#include "colorType.h"

#include "ray.h"
#include "shapes.h"
#include "stdlib.h"
#include "vector.h"
#include <math.h>

void initializeColorType(ColorType *color, float r, float g, float b) {
    color->r = r;
    color->g = g;
    color->b = b;
}

ColorType traceRay(RayType *ray, SphereType **sphereArray, int sizeOfArray,
                   ColorType *backgroundColor, Light* light) {
    
    // printf("%d\n", sizeOfArray);
    SphereType *sphere;
    float A;
    float B;
    float C;
    float t[sizeOfArray];

    Vector pointOfSphere;
    // printRay(ray);

    ColorType color;
    int minIndex = 0;
    for (int i = 0; i < sizeOfArray; i++) {
        sphere = sphereArray[i];

        A = pow(ray->dx, 2) + pow(ray->dy, 2) + pow(ray->dz, 2);
        if (A == 0) {
            printf("ray has a 0 vector for it's direction");
            initializeColorType(&color, -1, -1, -1);
            return color;
        }
        B = 2 * (ray->x - sphere->x) * ray->dx + 2 * (ray->y - sphere->y) * ray->dy +
            2 * (ray->z - sphere->z) * ray->dz;
        C = pow((ray->x - sphere->x), 2) + pow((ray->y - sphere->y), 2) +
            pow((ray->z - sphere->z), 2) - pow((sphere->radius), 2);

        if ((pow(B, 2) - 4 * A * C) < 0) {
            t[i] = -1;
            continue;
            // return *backgroundColor;
        } else if ((pow(B, 2) - 4 * A * C) == 0) {
            t[i] = (-1 * B) / (2 * A);

            // will be used for later iterations.
            initialize_vector(&pointOfSphere, ray->x + t[i] * ray->dx, ray->y + t[i] * ray->dy,
                              ray->z + t[i] * ray->dz);
            ///////////////

        } else {
            float t1 = (-1 * B + sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
            float t2 = (-1 * B - sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);

            if (t1 < 0 && t2 < 0) {
                t[i] = -1;
                continue;
            } else if (t1 < 0 && t2 > 0) {
                t[i] = t2;
            } else if (t1 > 0 && t2 < 0) {
                t[i] = t1;
            } else {
                if (t1 < t2) {
                    t[i] = t1;
                } else {
                    t[i] = t2;
                }
            }

            initialize_vector(&pointOfSphere, ray->x + t[i] * ray->dx, ray->y + t[i] * ray->dy,
                              ray->z + t[i] * ray->dz);

        }
    }
    // printf("tmin: %f\n", t[minIndex]);
    for (int i = 0; i < sizeOfArray; i++) {
        if (t[i] > -1 && t[minIndex] == -1) {
            minIndex = i;
        }
    
        if (t[i] < t[minIndex] && t[i] > -1) {
            minIndex = i;
        }
    }

    if (t[minIndex] == -1) {
        return *backgroundColor;
    }

    // initializeColorType(&color, sphereArray[minIndex]->r, sphereArray[minIndex]->g,
    //                     sphereArray[minIndex]->b);
    color = shadeRay("Sphere", sphereArray[minIndex], ray, &pointOfSphere, light, sphereArray, sizeOfArray);
    return color;
}

ColorType shadeRay(char* objectType, SphereType* sphere, RayType *ray,  Vector *surfacePoint,  Light* light, SphereType** sphereArray, int sizeOfArray){
    ColorType color;
    Vector intrinsicColor;
    Vector specularColor;
    Vector negSphereCenter;
    // Vector sphereSurface;
    Vector rayOrigin;
    Vector diffuseTerm;
    Vector V;
    Vector L;
    Vector H;


    // printRay(ray);
    // printVector(surfacePoint);
    // printVector(&light->lightLocation);

    
    if(initialize_vector(&negSphereCenter, -1 * sphere->x, -1 * sphere->y, -1 * sphere->z) == -1){
        printf("it died");
    }
    // initialize_vector(&sphereSurface, x, y, z);
    Vector rN = vectorAdd(surfacePoint, &negSphereCenter);
    Vector N = scalarVecMult(1.0/sphere->radius, &rN);
    // printf("N: ");
    // printVector(&N);
    initialize_vector(&rayOrigin, ray->x, ray->y, ray->z);
    Vector negSphereSurface = scalarVecMult(-1.0, surfacePoint);

    
    if(light->isPoint){
        // printf("LightLocation: (%f, %f, %f)", light->lightLocation.dx, light->lightLocation.dy, light->lightLocation.dz);
        L = vectorAdd(&light->lightLocation, &negSphereSurface);
        L = normalize(&L);
        
    }else {
        L = scalarVecMult(-1, &light->lightLocation);
        L = normalize(&L);
    }

    RayType lightRay;
    initializeRayType(&lightRay, surfacePoint->dx,surfacePoint->dy,  surfacePoint->dz);
    setDirection(&lightRay, L.dx, L.dy, L.dz);
    
    float A = 0.0;
    float B = 0.0;
    float C = 0.0;
    SphereType* obstructingSphere;
    int shadowFlag = 1;
    float t;

    for (int i = 0; i < sizeOfArray; i++){

        obstructingSphere = sphereArray[i];
        A = pow(lightRay.dx, 2) + pow(lightRay.dy, 2) + pow(lightRay.dz, 2);
        if (A == 0) {
            printf("light has a 0 vector for it's direction");
            initializeColorType(&color, -1, -1, -1);
            return color;
        }
        B = 2 * (lightRay.x - obstructingSphere->x) * lightRay.dx + 2 * (lightRay.y - obstructingSphere->y) * lightRay.dy +
            2 * (lightRay.z - obstructingSphere->z) * lightRay.dz;
        C = pow((lightRay.x - obstructingSphere->x), 2) + pow((lightRay.y - obstructingSphere->y), 2) +
            pow((lightRay.z - obstructingSphere->z), 2) - pow((obstructingSphere->radius), 2);

        if ((pow(B, 2) - 4 * A * C) < 0) {
                continue;
            // return *backgroundColor;
        } else if ((pow(B, 2) - 4 * A * C) == 0) {
            t = (-1 * B) / (2 * A);
            
                            
        } else {
            float t1 = (-1 * B + sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
            float t2 = (-1 * B - sqrt((pow(B, 2) - 4 * A * C))) / (2 * A);
            if(t1 < t2){
                t = t1;
            }else{
                t = t2;
            }
        }

        if(t <= 0){
            continue;
        }else{
            shadowFlag = 0;
            break;
        }
    }

    // printf("L: ");
    // printVector(&L);
    

    V = vectorAdd(&rayOrigin, &negSphereSurface);
    V = normalize(&V);

    // printf("V: ");
    // printVector(&V);
    H = vectorAdd(&L, &V);
    H = normalize(&H);

    
    if(initialize_vector(&intrinsicColor, sphere->Odr, sphere->Odg, sphere->Odb) == -1){
        printf("it actually died here\n");
    }
    if(initialize_vector(&specularColor, sphere->Osr, sphere->Osg, sphere->Osb) == -1){
        printf("probably not here then\n");
    }

    Vector ambientTerm = scalarVecMult(sphere->ka, &intrinsicColor);
    // printf("N: ");
    // printVector(&N);
    // printf("H: ");
    // printVector(&H);

    float nDotL = dotProduct(&N, &L);
    float nDotH = dotProduct(&N, &H);

    // printf("nDOtL: %f\n", nDotL);

    if(acos(nDotL) > M_PI/2){
        initialize_vector(&diffuseTerm, 0.0, 0.0, 0.0);
        // printf("%f\n", acos(nDotL));
        // printf("actually reached here\n");
    }else{
        
        // printf("%f\n", acos(nDotL));
        diffuseTerm = scalarVecMult(sphere->kd * nDotL, &intrinsicColor);
    }
    Vector specularTerm = scalarVecMult(sphere->ks * pow(fmax(0.0, nDotH),sphere->shinyFactor), &specularColor);
    Vector sum1 = vectorAdd(&specularTerm, &diffuseTerm);

    sum1 = scalarVecMult(light->lightIntensity * shadowFlag, &sum1);
    Vector sum2 = vectorAdd(&sum1, &ambientTerm);
    
    initializeColorType(&color, sum2.dx, sum2.dy, sum2.dz);

    if(color.r > 1){
        color.r = 1;
    }
    if(color.g > 1){
        color.g = 1;
    }
    if(color.b > 1){
        color.b = 1;
    }
    // printColor(&color);
    // printf("error is definitely here\n");
    
    
    return color;

}

void printColor(ColorType *color) {
    printf("color: (%f, %f, %f)\n", color->r, color->g, color->b);
}
