#include "vecList.h"
#include "shapes.h"
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 4

int vec_list_init(vec_list *list){
  list->length = 0;
  list->capacity = INITIAL_SIZE;
  list->data = malloc(INITIAL_SIZE * sizeof(Vector*));
  if(list->data == NULL){
    return -1;
  }
  return 0;
}


void vec_list_clear(vec_list *list){
  if (list->capacity == 0){
    return;
  }

  for (int i = 0; i < list->length; i++){
    free(list->data[i]);
  }
  free(list->data);

  list->length = 0;
  list->capacity = 0;
}


int vec_list_add(vec_list *list, Vector *vec){
  if (list->capacity == 0){
    if(vec_list_init(list) != 0){
      return -1;
    }
    
  }

  if(list->length == list->capacity){

    Vector **new_data = realloc(list->data, 2 * list->capacity * sizeof(Vector *));
  
    if(new_data == NULL){
      printf("entered here");
      return -1;
    }else{
      list->data = new_data;
    }
    // list->length = list->capacity;
    list->capacity = list->capacity * 2;
    printf("new capacity: %d\n", list->capacity);
    printf("length: %d\n", list->length);
  }

  // printf("is it actually here\n");

  // printf("in vec list: %d\n",  list->length);
  if((list->data[list->length] = malloc(sizeof(Vector))) == NULL){
    printf("problem is here\n");
    return -1;
  }
  // printf("are we here\n");
  // printf("in vec list: %d\n",  list->length);
  if(initialize_vector(list->data[list->length], vec->dx, vec->dy, vec->dz) == -1){
    printf("vector in vec_list_add contains nan\n");
  }

  list->length++;

  // printf("is the issue here?\n");
  
  return 0;

}


Vector *vec_list_get(vec_list *list, unsigned int index){
  if(index > list->length){
    return NULL;
  }
  if(index <= 0){
    return NULL;
  }

  return list->data[index - 1];
}


int tri_list_init(tri_list *list){
  
  list->length = 0;
  list->capacity = INITIAL_SIZE;
  list->data = malloc(INITIAL_SIZE * sizeof(Triangle*));
  if(list->data == NULL){
    return -1;
  }
  return 0;
}


void tri_list_clear(tri_list *list){
  
  if (list->capacity == 0){
    return;
  }

  for (int i = 0; i < list->length; i++){
    free(list->data[i]);
  }
  free(list->data);

  list->length = 0;
  list->capacity = 0;
}


int tri_list_add(tri_list *list, Triangle *tri){
  
  if (list->capacity == 0){
    if(tri_list_init(list) != 0){
      return -1;
    }
  
  }

  if(list->length == list->capacity){
    Triangle **new_data = realloc(list, 2 * list->capacity * sizeof(Triangle *));
    if(new_data == NULL){
      return -1;
    }else{
      list->data = new_data;
    }
    
    list->capacity = list->capacity * 2;
  }

  if((list->data[list->length] = malloc(sizeof(Triangle))) == NULL){
    return -1;
  }

  memcpy(list->data[list->length], tri, sizeof(Triangle));

  list->length++;
  //add the triangle here
  //
  ///////////
  
  return 0;
}

Triangle *tri_list_get(tri_list *list, unsigned int index){ 
  if(index > list->length){
    return NULL;
  }
  if(index <= 0){
    return NULL;
  }

  return list->data[index - 1];
}
