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


    char string[] = "1//134 2//2 3//3";

    char *token;
    token = strtok(string, "/");
    printf("%s\n", token);
    // token = strtok(NULL, "/");
    // printf("%s\n", token);
    token = strtok(NULL, " ");
    token = &token[1];
    printf("%s\n", token);
    
    return 0;
}
