#ifndef SPHERETYPE
#define SPHERETYPE

typedef struct {
    float x, y, z;
    float radius;
    float r, g, b;
    int m;
} SphereType;


void initializeSphere(SphereType* sphere, float x, float y, float z, float radius);

void setColor(SphereType* sphere, float r, float g, float b);
#endif