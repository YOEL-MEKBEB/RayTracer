#include "vecList.h"
#include <stdlib.h>

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
    Vector **new_data = realloc(list, 2 * list->capacity * sizeof(Vector *));
    if(new_data == NULL){
      return -1;
    }else{
      list->data = new_data;
    }
    
    list->capacity = list->capacity * 2;
  }

  if((list->data[list->length] = malloc(sizeof(Vector))) == NULL){
    return -1;
  }

  initialize_vector(list->data[list->length], vec->dx, vec->dy, vec->dz);

  list->length++;
  
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
