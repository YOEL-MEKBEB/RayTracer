#ifndef VECTOR
#define VECTOR
#include <math.h>
#include <stdio.h>

typedef struct {
    float dx, dy, dz;
} Vector;

void initialize_vector(Vector* vector, float dx, float dy, float dz);
Vector vectorAdd(Vector* vector1, Vector* vector2);
float dotProduct(Vector* vector1, Vector* vector2);
Vector crossProduct(Vector* vector1, Vector* vector2);
float vectorLength(Vector* vector);
Vector scalarVecMult(float scalar, Vector *vector);
Vector normalize(Vector* vector);
#endif
