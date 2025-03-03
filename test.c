#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stdlib.h"
#include "string.h"
#include <math.h>

#include "vecList.h"
#include "vector.h"
/// @brief calls strtof and handles error where it returns 0 on text
/// @param token
/// @return returns the converted value on success or NAN on error
float protectedStrToF(char *token) {
    float value = strtof(token, NULL);
    if (strtof(token, NULL) == 0.0){
        if(strcmp("0", token) != 0 && strcmp("0.0", token) != 0) {
            return NAN;
        }
    }
    return value;
}


int main() {
    // Camera *camera = malloc(sizeof(Camera));
    // ColorType *backgroundColor = malloc(sizeof(ColorType));

    vec_list *vertices = malloc(sizeof(vec_list));

    Vector new_vec;
    initialize_vector(&new_vec, 0.0, 0.0, 0.0);

    
    vec_list_add(vertices, &new_vec);

    printf("%u\n", vertices->length);
    printVector(vec_list_get(vertices, 1));
    return 0;
}
