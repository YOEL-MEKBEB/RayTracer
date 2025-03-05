
#ifndef VEC_LIST_H
#define VEC_LIST_H

#include "vector.h"
#include "shapes.h"

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

#ifndef TRI_LIST_H
#define TRI_LIST_H
typedef struct {
    unsigned int length;
    unsigned int capacity;
    Triangle **data;
}tri_list;

int tri_list_init(tri_list *list);

void tri_list_clear(tri_list *list);

int tri_list_add(tri_list *list, Triangle *tri);

Triangle *tri_list_get(tri_list *list, unsigned index);
#endif
