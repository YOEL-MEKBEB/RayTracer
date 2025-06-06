#include "shapes.h"

#include <math.h>

#include "stdio.h"
#include "vector.h"
int initializeSphere(SphereType *sphere, float x, float y, float z, float radius, int m,
                     int useTexture, float backgroundRefraction) {
    if (isnan(x) || isnan(y) || isnan(z) || isnan(radius)) {
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
    sphere->useTexture = useTexture;
    sphere->opacity = 1;
    sphere->indexOfRefraction = 1;
    sphere->backgroundRefraction = backgroundRefraction;
    return 0;
}

int setIntrinsicColor(SphereType *sphere, float r, float g, float b) {
    if (isnan(r) || isnan(g) || isnan(b)) {
        printf("colors are not a number\n");
        return -1;
    }

    sphere->Odr = r;
    sphere->Odg = g;
    sphere->Odb = b;
    return 0;
}

int setSpecularColor(SphereType *sphere, float r, float g, float b) {
    if (isnan(r) || isnan(g) || isnan(b)) {
        printf("colors are not a number\n");
        return -1;
    }
    sphere->Osr = r;
    sphere->Osg = g;
    sphere->Osb = b;
    return 0;
}

int setWeight(SphereType *sphere, float ka, float kd, float ks) {
    if (isnan(ka) || isnan(kd) || isnan(ks)) {
        printf("weights are not a number\n");
        return -1;
    }

    sphere->ka = ka;
    sphere->kd = kd;
    sphere->ks = ks;
    return 0;
}

int setShinyFactor(SphereType *sphere, int shinyFactor) {
    sphere->shinyFactor = shinyFactor;
    return 0;
}

int setOpacityAndRefraction(SphereType *sphere, float opacity, float indexOfRefraction){
    if(isnan(opacity) || isnan(indexOfRefraction)){
        printf("opacity or index of refraction are not numbers");
        printf("opacity: %f\n", opacity);
        printf("index of refraction: %f\n", indexOfRefraction);
        return -1;
    }
    sphere->opacity = opacity;
    sphere->indexOfRefraction = indexOfRefraction;
    return 0;
}

void printSphere(SphereType *sphere) {
    printf("sphere position: (x, y, z) = (%f, %f, %f)\n", sphere->x, sphere->y, sphere->z);
    printf("sphere Intrinsic color: (Odr, Odg, Odb) = (%f, %f, %f)\n", sphere->Odr, sphere->Odg,
           sphere->Odb);
    printf("sphere specular color: (Osr, Osg, Osb) = (%f, %f, %f)\n", sphere->Osr, sphere->Osg,
           sphere->Osb);
    printf("sphere weights: (ka, kd, ks) = (%f, %f, %f)\n", sphere->ka, sphere->kd, sphere->ks);
    printf("Sphere shiny factor = %d\n", sphere->shinyFactor);
    printf("sphere radius:  = %f\n", sphere->radius);
    printf("sphere tag:  = %d\n", sphere->m);
    printf("use texture: %d\n", sphere->useTexture);
    printf("opacity: %f\n", sphere->opacity);
    printf("index of refraction: %f\n\n", sphere->indexOfRefraction);
}

int initializeTriangle(Triangle *triangle, float v1, float v2, float v3, int isSmooth,
                       int useTexture, float backgroundRefraction) {
    if (isnan(v1) || isnan(v2) || isnan(v3)) {
        printf("triangle coordinates are not a number\n");
        return -1;
    }
    triangle->face.dx = v1;
    triangle->face.dy = v2;
    triangle->face.dz = v3;

    triangle->normal.dx = 0;
    triangle->normal.dy = 0;
    triangle->normal.dz = 0;

    triangle->texture.dx = 0;
    triangle->texture.dy = 0;
    triangle->texture.dz = 0;

    triangle->Odr = 0.0;
    triangle->Odg = 0.0;
    triangle->Odb = 0.0;

    triangle->Osr = 0.0;
    triangle->Osg = 0.0;
    triangle->Osb = 0.0;

    triangle->ka = 0.0;
    triangle->kd = 0.0;
    triangle->ks = 0.0;

    triangle->shinyFactor = 0;

    triangle->isSmoothShaded = isSmooth;
    triangle->useTexture = useTexture;

    triangle->opacity = 1;
    triangle->indexOfRefraction = 1;
    triangle->backgroundRefraction = backgroundRefraction;

    return 0;
}

int setTriangleNormal(Triangle *triangle, float n1, float n2, float n3) {
    if (isnan(n1) || isnan(n2) || isnan(n3)) {
        printf("Triangle normals are not a number\n");
        return -1;
    }

    triangle->normal.dx = n1;
    triangle->normal.dy = n2;
    triangle->normal.dz = n3;

    return 0;
}
int setTriangleTexture(Triangle *triangle, float t1, float t2, float t3) {
    if (isnan(t1) || isnan(t2) || isnan(t3)) {
        printf("Triangle normals are not a number\n");
        return -1;
    }

    triangle->texture.dx = t1;
    triangle->texture.dy = t2;
    triangle->texture.dz = t3;

    return 0;
}

int setIntrinsicTriangle(Triangle *triangle, float r, float g, float b) {
    if (isnan(r) || isnan(g) || isnan(b)) {
        printf("Triangle colors are not a number\n");
        return -1;
    }

    triangle->Odr = r;
    triangle->Odg = g;
    triangle->Odb = b;
    return 0;
}

int setSpecularTriangle(Triangle *triangle, float r, float g, float b) {
    if (isnan(r) || isnan(g) || isnan(b)) {
        printf("Triangle specular colors are not a number\n");
        return -1;
    }

    triangle->Osr = r;
    triangle->Osg = g;
    triangle->Osb = b;
    return 0;
}

int setTriangleWeight(Triangle *triangle, float ka, float kd, float ks) {
    if (isnan(ka) || isnan(kd) || isnan(ks)) {
        printf("Triangle weights are not a number\n");
        return -1;
    }

    triangle->ka = ka;
    triangle->kd = kd;
    triangle->ks = ks;
    return 0;
}

int setTriangleShinyFactor(Triangle *triangle, int shinyFactor) {
    triangle->shinyFactor = shinyFactor;
    return 0;
}

int setOpacityAndRefractionTriangle(Triangle *triangle, float opacity, float indexOfRefraction){

    if(isnan(opacity) || isnan(indexOfRefraction)){
        printf("opacity or index of refraction are not numbers");
        printf("opacity: %f\n", opacity);
        printf("index of refraction: %f\n", indexOfRefraction);
        return -1;
    }
    triangle->opacity = opacity;
    triangle->indexOfRefraction = indexOfRefraction;
    return 0;
}

void printTriangle(Triangle *triangle) {
    printf("triangle vertices: (x, y, z) = (%f, %f, %f)\n", triangle->face.dx, triangle->face.dy,
           triangle->face.dz);
    printf("triangle normal: ");
    printVector(&triangle->normal);
    printf("triangle Intrinsic color: (Odr, Odg, Odb) = (%f, %f, %f)\n", triangle->Odr,
           triangle->Odg, triangle->Odb);
    printf("triangle specular color: (Osr, Osg, Osb) = (%f, %f, %f)\n", triangle->Osr,
           triangle->Osg, triangle->Osb);
    printf("triangle weights: (ka, kd, ks) = (%f, %f, %f)\n", triangle->ka, triangle->kd,
           triangle->ks);
    printf("triangle shiny factor = %d\n", triangle->shinyFactor);
    printf("triangle isSmoothShaded = %d\n", triangle->isSmoothShaded);
    printf("triangle useTexture = %d\n", triangle->useTexture);
    printf("opacity: %f\n", triangle->opacity);
    printf("index of refraction: %f\n\n", triangle->indexOfRefraction);
}
