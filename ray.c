#include "ray.h"
#include "stdlib.h"

void initializeRayType(RayType *ray, int dx, int dy, int dz){
    ray->x = 0;
    ray->y = 0;
    ray->z = 0;
    ray->dx = dx;
    ray->dy = dy;
    ray->dz = dz;

}
float rayDotProduct(RayType *ray1, RayType *ray2){
    return ray1->dx * ray2->dx + ray1->dy * ray2->dy + ray1->dz + ray2->dz;
}

RayType* rayCrossProduct(RayType *ray1, RayType *ray2){
    RayType* product = malloc(sizeof(RayType));
    product->x = ray1->x;
    product->y = ray1->y;
    product->z = ray1->z;

    product->dx = ray1->dy * ray2->dz - (ray1->dz * ray2->dy);
    product->dy = ray1->dz * ray2->dx - (ray1->dx * ray2->dz);
    product->dz = ray1->dx * ray2->dy - (ray1->dy * ray2->dx);


    return product;
}

RayType* RaySum(RayType *ray1, RayType *ray2){
    RayType* sum = malloc(sizeof(RayType));
    sum->x = ray1->x;
    sum->y = ray1->y;
    sum->z = ray1->z;

    sum->dx = ray1->dx + ray2->dx;
    sum->dy = ray1->dy + ray2->dy;
    sum->dz = ray1->dz + ray2->dz;

    return sum;
}

RayType* scalarRayMult(float scalar, RayType *ray){
    RayType* result = ray;
    result->dx = scalar * ray->dx;
    result->dy = scalar * ray->dy;
    result->dz = scalar * ray->dz;

    return result;
}

float Raylength(RayType *ray){
    return sqrt(pow(ray->dx, 2) + pow(ray->dy, 2) + pow(ray->dz, 2));
}

int recordColor(RayType *ray, float r, float g, float b){
    if(r > 1 || g > 1 || b > 1){
        printf("the r, g, or b value of the color is greater than one\n please normalize it.");
        return -1;
    }
    ray->r = r;
    ray->g = g;
    ray->b = b;
    return 0;
}

void printRay(RayType *ray){
    printf("x = %f\n", ray->x);
    printf("y = %f\n", ray->y);
    printf("z = %f\n", ray->z);
    printf("dx = %f\n", ray->dx);
    printf("dy = %f\n", ray->dy);
    printf("dz = %f\n", ray->dz);
}