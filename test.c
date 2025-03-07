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


int read(vec_list **image, char *fileName){
    
    FILE *file = fopen(fileName, "r");
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

    int MAXSIZE = width * height;
    char buf2[MAXSIZE];
    

    for(int i = 0; i < height; i++){
        
        
        fgets(buf2, MAXSIZE, file);

        printf("%s", buf2);

        char delimeter[] = " \n";

        token = strtok(buf2, delimeter);

        int k = 0;
        while(token != NULL){
            k++;
            printf("%s\n", token);
            token = strtok(NULL, delimeter);
        }


                
    }


    
    // while(fread(buf,1,100,file) > 0){
    //     i++;
    //     printf("%s", buf);
    // }
    // printf("%d\n", i);
  
  return 0;
}




int main() {
    // Camera *camera = malloc(sizeof(Camera));
    // ColorType *backgroundColor = malloc(sizeof(ColorType));

    char filename[] = "texture/cat.ppm";

    vec_list **image;
    read(image, filename);

    
    
    
    
    return 0;
}
