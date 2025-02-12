#ifndef VECTOR
#define VECTOR
#include <math.h>
#include <stdio.h>

typedef struct {
    float dx, dy, dz;
} Vector;

/// @brief initializes the vector to be used by assigning the float values to the respective axis
/// in vector
/// @param vector a vector pointer to assign the coordinates
/// @param dx x coordinate of the vector
/// @param dy y coordinate of the vector
/// @param dz z coordinate of the vector
void initialize_vector(Vector *vector, float dx, float dy, float dz);

/// @brief calculates the sum of the 2 vectors provided on success
/// @param vector1
/// @param vector2
/// @return returns a new vector
Vector vectorAdd(Vector *vector1, Vector *vector2);

/// @brief calculates the dot product of the 2 vectors provided
/// @param vector1
/// @param vector2
/// @return returns a float
float dotProduct(Vector *vector1, Vector *vector2);

/// @brief calculates the cross product of the 2 vectors
/// @param vector1
/// @param vector2
/// @return returns a new vector
Vector crossProduct(Vector *vector1, Vector *vector2);

/// @brief uses the euclidean norm to calculate the magnitude of the vector
/// @param vector
/// @return  returns the magnitude of the vector
float vectorLength(Vector *vector);

/// @brief calculates the product of the scalar value and the vector
/// @param scalar
/// @param vector
/// @return returns a new vector
Vector scalarVecMult(float scalar, Vector *vector);

/// @brief  calculates the normalized version of the vector
/// @param vector
/// @return returns a new vector. If a 0 vector is provided then the vector is returned as is
Vector normalize(Vector *vector);
#endif
