#include "ppmReader.h"
#include <stdio.h>
#include "vecList.h"
#include "vector.h"
#include <stdlib.h>
#include <string.h>

float protectedStrToF(char *token) {
    float value = strtof(token, NULL);
    if (strtof(token, NULL) == 0.0){
        if(strcmp("0", token) != 0 && strcmp("0.0", token) != 0 && strcmp("0\r", token) != 0 && strcmp("0.0\r", token)) {
            return NAN;
        }
    }
    return value;
}
 int ppmRead(vec_list **image, FILE* file, int width, int height){
  
    char *token;
    char *memorizer;
    printf("%d %d\n", width, height);

    int MAXSIZE = width * height;
    char buf2[MAXSIZE];
    

    char delimeter[] = " \n";
    float x;
    float y;
    float z;
    
    for(int i = 0; i < height; i++){
        
        
        fgets(buf2, MAXSIZE, file);

        // printf("%s", buf2);


        token = strtok_r(buf2, delimeter, &memorizer);

        // printf("%s\n", token);
        vec_list *list = malloc(sizeof(vec_list));
        vec_list_init(list);
        while(token != NULL && strcmp(token, "\r") != 0){
            // printf("this is the capacity: %d\n", list->capacity);
            
            x = protectedStrToF(token)/255.0;
            y = protectedStrToF(strtok_r(memorizer, delimeter, &memorizer))/255.0;
            z = protectedStrToF(strtok_r(memorizer, delimeter, &memorizer))/255.0;
            Vector vec;
            initialize_vector(&vec, x, y, z);
            vec_list_add(list, &vec);
            token = strtok_r(memorizer, delimeter, &memorizer);
        }
        // printf("is it here\n");
        image[i] = list;
                
    }

   
  
  return 0;
  


  
}
