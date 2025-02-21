#include "shapes.h"

#include "stdio.h"
#include <math.h>
int initializeSphere(SphereType* sphere, float x, float y, float z, float radius, int m){

    if(isnan(x) || isnan(y) || isnan(z) || isnan(radius)){
        printf("sphere coordinates are not a number\n");
        return -1;
    }
    sphere->x = x;
    sphere->y = y;
    sphere->z = z;
    sphere->radius = radius;
    sphere->m = m;

    sphere->Odr = 0.0;
    sphere->Odg = 0.0;
    sphere->Odb = 0.0;

    
    sphere->Osr = 0.0;
    sphere->Osg = 0.0;
    sphere->Osb = 0.0;
    
    sphere->ka = 0.0;
    sphere->kd = 0.0;
    sphere->ks = 0.0;

    sphere->shinyFactor = 0;
    return 0;

}

int setIntrinsicColor(SphereType* sphere, float r, float g, float b){

    if(isnan(r) || isnan(g) || isnan(b)){
        printf("colors are not a number\n");
        return -1;
    }
    
    sphere->Odr = r;
    sphere->Odg = g;
    sphere->Odb = b;
    return 0;
}

int setSpecularColor(SphereType *sphere, float r, float g, float b){
    
    if(isnan(r) || isnan(g) || isnan(b)){
        printf("colors are not a number\n");
        return -1;
    }
    sphere->Osr = r;
    sphere->Osg = g;
    sphere->Osb = b;
    return 0;
}

int setWeight(SphereType *sphere, float ka, float kd, float ks){
    
    if(isnan(ka) || isnan(kd) || isnan(ks)){
        printf("weights are not a number\n");
        return -1;
    }

    sphere->ka = ka;
    sphere->kd = kd;
    sphere->ks = ks;
    return 0;
}


int setShinyFactor(SphereType *sphere, int shinyFactor){
    if(isnan(shinyFactor)){
        printf("shinyFactor is not one");
        return -1;
    }
    sphere->shinyFactor = shinyFactor;
    return 0;
}
void printSphere(SphereType *sphere){
    printf("sphere position: (x, y, z) = (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
    printf("sphere Intrinsic color: (Odr, Odg, Odb) = (%f, %f, %f)\n", sphere->Odr, sphere->Odg, sphere->Odb);
    printf("sphere specular color: (Osr, Osg, Osb) = (%f, %f, %f)\n", sphere->Osr, sphere->Osg, sphere->Osb);
    printf("sphere weights: (ka, kd, ks) = (%f, %f, %f)\n", sphere->ka, sphere->kd, sphere->ks);
    printf("Sphere shiny factor = %d\n", sphere->shinyFactor);
    printf("sphere radius:  = %f\n", sphere->radius);
    printf("sphere tag:  = %d\n\n", sphere->m);

}
