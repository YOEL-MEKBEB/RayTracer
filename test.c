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


int read(vec_list **image, FILE* file, int width, int height){
    
    // FILE *file = fopen(fileName, "r");
    // char buf[1024];



    // fgets(buf, 1024, file);
    char *token;

    
    // if(strcmp(token, "P3") != 0){
    //     printf("not proper ppm file\n");
    //     return -1;
    // }

    // int width = atoi(strtok(NULL, " "));
    // int height = atoi(strtok(NULL, " "));



    // image = malloc(height * sizeof(vec_list*));
    
    printf("%d %d\n", width, height);

    int MAXSIZE = width * height;
    char buf2[MAXSIZE];
    

    char delimeter[] = " \n";
    float x;
    float y;
    float z;
    
    for(int i = 0; i < height; i++){
        
        
        fgets(buf2, MAXSIZE, file);

        printf("%s", buf2);


        token = strtok(buf2, delimeter);

        printf("%s\n", token);
        vec_list *list = malloc(sizeof(vec_list));
        vec_list_init(list);
        while(token != NULL){
            // printf("this is the capacity: %d\n", list->capacity);
            
            x = protectedStrToF(token);
            y = protectedStrToF(strtok(NULL, delimeter));
            z = protectedStrToF(strtok(NULL, delimeter));
            Vector vec;
            initialize_vector(&vec, x, y, z);
            vec_list_add(list, &vec);
            token = strtok(NULL, delimeter);
        }
        image[i] = list;
                
    }

   
  
  return 0;
}




int main() {
    // Camera *camera = malloc(sizeof(Camera));
    // ColorType *backgroundColor = malloc(sizeof(ColorType));

    char filename[] = "texture/cat.ppm";
    vec_list **image;
    
    FILE *file = fopen(filename, "r");
    char buf[1024];



    fgets(buf, 1024, file);
    char *token = strtok(buf, " ");

    
    if(strcmp(token, "P3") != 0){
        printf("not proper ppm file\n");
        return -1;
    }

    int width = atoi(strtok(NULL, " "));
    int height = atoi(strtok(NULL, " "));

    image = malloc(height * sizeof(vec_list*));
    
    printf("%d %d\n", width, height);

    read(image, file, width, height);
    // printf("it's here\n");
    // printf("%d\n", height);

    for(int i = 0; i < height; i++){
        vec_list *list = image[i];

        
        for(int j = 1; j< list->length+1; j++){
            // printf("entered double loop\n");
            printVector(vec_list_get(list, j));
        }
        printf("%d\n", i);
        vec_list_clear(list);
    }

    
    
    
    
    return 0;
}
