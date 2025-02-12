#include "colorType.h"
#include "stdlib.h"

void initializeColorType(ColorType* color, float r, float g, float b){
    color->r = r;
    color->g = g;
    color->b = b;
}

ColorType traceRay(RayType *ray, SphereType** sphereArray,int sizeOfArray,  ColorType* backgroundColor){
    // printf("%d\n", sizeOfArray);
    SphereType* sphere;
    float A;
    float B;
    float C;
    float t[sizeOfArray];

    ColorType color;
    int minIndex=0;
   for(int i = 0; i < sizeOfArray; i++){

        sphere = sphereArray[i];
       
        A = pow(ray->dx,2) + pow(ray->dy,2) + pow(ray->dz,2);
        B = 2* (ray->x - sphere->x) * ray->dx + 2* (ray->y - sphere->y) * ray->dy + 2* (ray->z - sphere->z) * ray->dz;
        C = pow((ray->x - sphere->x), 2) + pow((ray->y - sphere->y), 2) + pow((ray->z - sphere->z), 2) - pow((sphere->radius), 2);

        if((pow(B,2) - 4 * A * C) < 0){
            t[i] = -1;
            continue;
             // return *backgroundColor;
        }else if((pow(B,2) - 4 * A * C) == 0){
            t[i] = (-1 * B)/(2*A);

            // will be used for later iterations.
            Vector pointOfSphere;
            initialize_vector(&pointOfSphere, ray->x + t[i] * ray->dx, ray->y + t[i] * ray->dy, ray->z + t[i] * ray->dz);
            ///////////////

            // initializeColorType(&color, sphere->r, sphere->g, sphere->b);

            // return color;
            
        }else{
            float t1 = (-1 * B + sqrt((pow(B,2) - 4 * A * C)))/(2*A);
            float t2 = (-1 * B - sqrt((pow(B,2) - 4 * A * C)))/(2*A);

            if(t1 < 0 && t2 < 0){
                continue;
            }else if (t1 < 0 && t2 > 0){
                t[i] = t2;
            }else if(t1 > 0 && t2 < 0){
                t[i] = t1;
            }else{
                if(t1 < t2){
                    t[i] = t1;
                }else{
                    t[i] = t2;
                }
            }

            // only usefull for future iteration
            Vector pointOfSphere;
            initialize_vector(&pointOfSphere, ray->x + t[i] * ray->dx, ray->y + t[i] * ray->dy, ray->z + t[i] * ray->dz);
            ///////////////

            // initializeColorType(&color, sphere->r, sphere->g, sphere->b);
            // return color;
        }
   }
      // printf("tmin: %f\n", t[minIndex]);
    for(int i = 0; i < sizeOfArray; i++){
        if(t[i] > -1 && t[minIndex] == -1){
            minIndex = i;
        }
        // this is where the logic breaks
        if (t[i] < t[minIndex] && t[i]>-1) {
            minIndex = i;
        }
    }
    
    if(t[minIndex] == -1){
        return *backgroundColor;
    }

    printf("min index: %d\n", minIndex);
    initializeColorType(&color, sphereArray[minIndex]->r, sphereArray[minIndex]->g, sphereArray[minIndex]->b);
    return color;
        // printf("%d\n", i);
        // printSphere(sphere);
        //printRay(ray);
        


    // if((pow(B,2) - 4 * A * C) < 0){
    //     return backgroundColor;
    // }else if((pow(B,2) - 4 * A * C) == 0){
    //     t = (-1 * B)/(2*A);

    //     // will be used for later iterations.
    //     Vector pointOfSphere;
    //     initialize_vector(&pointOfSphere, ray->x + t * ray->dx, ray->y + t * ray->dy, ray->z + t * ray->dz);
    //     ///////////////

    //     ColorType* color = malloc(sizeof(ColorType));
    //     initializeColorType(color, sphere->r, sphere->g, sphere->b);

    //     return color;
        
    // }else{
    //     float t1 = (-1 * B + sqrt((pow(B,2) - 4 * A * C)))/(2*A);
    //     float t2 = (-1 * B - sqrt((pow(B,2) - 4 * A * C)))/(2*A);

    //     t = 0;
    //     if(t1 < 0 && t2 < 0){
    //         return backgroundColor;
    //     }else if (t1 < 0 && t2 > 0){
    //         t = t2;
    //     }else if(t1 > 0 && t2 < 0){
    //         t = t1;
    //     }else{
    //         if(t1 < t2){
    //             t = t1;
    //         }else{
    //             t = t2;
    //         }
    //     }

    //     // only usefull for future iteration
    //     Vector pointOfSphere;
    //     initialize_vector(&pointOfSphere, ray->x + t * ray->dx, ray->y + t * ray->dy, ray->z + t * ray->dz);
    //     ///////////////

    //     ColorType* color = malloc(sizeof(ColorType));
    //     initializeColorType(color, sphere->r, sphere->g, sphere->b);
    //     return color;
    // }
}


ColorType shadeRay(char* parameter){
    
}

void printColor(ColorType* color){
    printf("color: (%f, %f, %f)\n", color->r, color->g, color->b);    
}
