#include "vector.h"

void initialize_vector(Vector* vector, float dx, float dy, float dz){
    vector->dx = dx;
    vector->dy = dy;
    vector->dz = dz;
}

Vector vectorAdd(Vector* vector1, Vector* vector2){
    Vector sum;
    initialize_vector(&sum, vector1->dx + vector2->dx, vector1->dy + vector2->dy, vector1->dz + vector2->dz);
    return sum;
}
float dotProduct(Vector* vector1, Vector* vector2){
    return vector1->dx * vector2->dx + vector1->dy * vector2->dy + vector1->dz * vector2->dz;
}

Vector crossProduct(Vector* vector1, Vector* vector2){
    Vector product;
    float x = vector1->dy * vector2->dz - (vector1->dz * vector2->dy); 
    float y = vector1->dz * vector2->dx - (vector1->dx * vector2->dz); 
    float z = vector1->dx * vector2->dy - (vector1->dy * vector2->dx); 

    initialize_vector(&product, x, y, z);
    return product;
}
float vectorLength(Vector* vector){
    return sqrt(pow(vector->dx, 2) + pow(vector->dy, 2) + pow(vector->dz, 2));
}

Vector scalarVecMult(float scalar, Vector *vector){
    Vector result;
    float dx = scalar * vector->dx;
    float dy = scalar * vector->dy;
    float dz = scalar * vector->dz;

    initialize_vector(&result, dx, dy, dz);
    return result;
}
Vector normalize(Vector* vector){
    return scalarVecMult(1/(vectorLength(vector)), vector);
}