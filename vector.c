#include "vector.h"

int initialize_vector(Vector* vector, float dx, float dy, float dz){

    if(isnan(dx) || isnan(dy) || isnan(dz)){
        printf("dx, dy, or dz is not a number\n");
        printf("dx: %f\n", dx);
        printf("dy: %f\n", dy);
        printf("dz: %f\n", dz);
        return -1;
    }


    
    vector->dx = dx;
    vector->dy = dy;
    vector->dz = dz;
    return 0;
}

Vector vectorAdd(Vector* vector1, Vector* vector2){
    Vector sum;
    if(initialize_vector(&sum, vector1->dx + vector2->dx, vector1->dy + vector2->dy, vector1->dz + vector2->dz) == -1){
        printf("the problem is here\n");
    }
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
    if(isnan(scalar)){
        printf("scalar is not a number\n");
    }
    Vector result;
    // printVector(vector);
    // printf("scalar: %f\n", scalar);
    float dx = scalar * vector->dx;
    float dy = scalar * vector->dy;
    float dz = scalar * vector->dz;

    if(initialize_vector(&result, dx, dy, dz) == -1){
        printf("the issue is in scalar vec mult\n");
    }
    return result;
}
Vector normalize(Vector* vector){
    if(vectorLength(vector)==0){
        return *vector;
    }
    return scalarVecMult(1/(vectorLength(vector)), vector);
}

void printVector(Vector *vector){
    printf("vector: (%f, %f, %f)\n", vector->dx, vector->dy, vector->dz);
}
