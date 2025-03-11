#include "ppmReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vecList.h"
#include "vector.h"

float protectedStrToF(char *token) {
    float value = strtof(token, NULL);
    if (strtof(token, NULL) == 0.0) {
        if (strcmp("0", token) != 0 && strcmp("0.0", token) != 0 && strcmp("0\r", token) != 0 &&
            strcmp("0.0\r", token)) {
            return NAN;
        }
    }
    return value;
}
int ppmRead(vec_list **image, FILE *file, int width, int height) {
    char *token;
    char *memorizer;    // char pointer used for strtok_r
    printf("%d %d\n", width, height);

    int MAXSIZE = width * height;
    char buf2[MAXSIZE];

    char delimeter[] = " \n";
    float x;
    float y;
    float z;
    // reads 3 numbers at once and stores the rgb values in a vec_list
    for (int i = 0; i < height; i++) {
        // obtains the entire row of the ppm file
        fgets(buf2, MAXSIZE, file);

        token = strtok_r(buf2, delimeter, &memorizer);

        vec_list *list = malloc(sizeof(vec_list));
        vec_list_init(list);

        while (token != NULL && strcmp(token, "\r") != 0) {
            x = protectedStrToF(token) / 255.0;
            y = protectedStrToF(strtok_r(memorizer, delimeter, &memorizer)) / 255.0;
            z = protectedStrToF(strtok_r(memorizer, delimeter, &memorizer)) / 255.0;
            Vector vec;
            initialize_vector(&vec, x, y, z);
            vec_list_add(list, &vec);
            token = strtok_r(memorizer, delimeter, &memorizer);
        }
        image[i] = list;
    }

    return 0;
}
