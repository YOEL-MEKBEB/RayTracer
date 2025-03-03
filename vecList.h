
#ifndef VEC_LIST_H
#define VEC_LIST_H

#include "vector.h"

typedef struct {
    unsigned int length;
    unsigned int capacity;
    Vector **data;
} vec_list;



int vec_list_init(vec_list *list);

void vec_list_clear(vec_list *list);

int vec_list_add(vec_list *list, Vector *vec);

Vector *vec_list_get(vec_list *list, unsigned index);


#endif
