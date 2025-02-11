#include "colorType.h"
#include "stdlib.h"

void initializeColorType(ColorType* color, float r, float g, float b){
    color->r = r;
    color->g = g;
    color->b = b;
}

ColorType* traceRay(RayType *ray, SphereType* sphere, ColorType* backgroundColor){
    // int length = sizeof(sphereArray)/sizeof(sphereArray[0]);
    // printf("sizeOf sphereArray: %lu\n", sizeof(sphereArray));
    // printf("sizeOf sphereArray[0]: %lu\n", sizeof(sphereArray[0]));
    // printSphere(sphereArray[1]);
    // // printf("%d\n", length);
    // SphereType* sphere;
    float A;
    float B;
    float C;
    float t = 0.0;
   
        // printf("%d\n", i);
        // sphere = sphereArray[i];
        // printSphere(sphere);
        printRay(ray);
        A = pow(ray->dx,2) + pow(ray->dy,2) + pow(ray->dz,2);
        B = 2* (ray->x - sphere->x) * ray->dx + 2* (ray->y - sphere->y) * ray->dy + 2* (ray->z - sphere->z) * ray->dz;
        C = pow((ray->x - sphere->x), 2) + pow((ray->y - sphere->y), 2) + pow((ray->z - sphere->z), 2) - pow((sphere->radius), 2);
        


    if((pow(B,2) - 4 * A * C) < 0){
        return backgroundColor;
    }else if((pow(B,2) - 4 * A * C) == 0){
        t = (-1 * B)/(2*A);

        // will be used for later iterations.
        Vector pointOfSphere;
        initialize_vector(&pointOfSphere, ray->x + t * ray->dx, ray->y + t * ray->dy, ray->z + t * ray->dz);
        ///////////////

        ColorType* color = malloc(sizeof(ColorType));
        initializeColorType(color, sphere->r, sphere->g, sphere->b);

        return color;
        
    }else{
        float t1 = (-1 * B + sqrt((pow(B,2) - 4 * A * C)))/(2*A);
        float t2 = (-1 * B - sqrt((pow(B,2) - 4 * A * C)))/(2*A);

        t = 0;
        if(t1 < 0 && t2 < 0){
            return backgroundColor;
        }else if (t1 < 0 && t2 > 0){
            t = t2;
        }else if(t1 > 0 && t2 < 0){
            t = t1;
        }else{
            if(t1 < t2){
                t = t1;
            }else{
                t = t2;
            }
        }

        // only usefull for future iteration
        Vector pointOfSphere;
        initialize_vector(&pointOfSphere, ray->x + t * ray->dx, ray->y + t * ray->dy, ray->z + t * ray->dz);
        ///////////////

        ColorType* color = malloc(sizeof(ColorType));
        initializeColorType(color, sphere->r, sphere->g, sphere->b);
        return color;
    }
}


// ColorType shadeRay(char* parameter);

void printColor(ColorType* color){
    printf("color: (%f, %f, %f)", color->r, color->g, color->b);    
}
