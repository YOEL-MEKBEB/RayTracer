#include "vecList.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_SIZE 4


int vec_list_init(vec_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    
    list->data = malloc(INITIAL_SIZE * sizeof(Vector));
    
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void vec_list_clear(vec_list *list) {
    if (list->capacity == 0) {
        return;
    }

    free(list->data);

    list->length = 0;
    list->capacity = 0;
    list->data = NULL;
}

int vec_list_add(vec_list *list, Vector *vec) {
    if (list->capacity == 0) {
        if (vec_list_init(list) != 0) {
            return -1;
        }
    }

    if (list->length == list->capacity) {
        Vector *new_data = realloc(list->data, 2 * list->capacity * sizeof(Vector));

        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }
        list->capacity = list->capacity * 2;
    }

    // My original data structure was not cache-friendly(late realization)
    //  I'm getting the actual value instead of the pointer and don't want to refactor the entire code
    list->data[list->length] = *vec;

    list->length++;
    return 0;
}

Vector *vec_list_get(vec_list *list, unsigned int index) {
    if (index > list->length || index <= 0) {
        return NULL;
    }

    return &list->data[index - 1];
}

int tri_list_init(tri_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    
    list->data = malloc(INITIAL_SIZE * sizeof(Triangle));
    
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void tri_list_clear(tri_list *list) {
    if (list->capacity == 0) {
        return;
    }

    free(list->data);

    list->length = 0;
    list->capacity = 0;
    list->data = NULL;
}

int tri_list_add(tri_list *list, Triangle *tri) {
    if (list->capacity == 0) {
        if (tri_list_init(list) != 0) {
            return -1;
        }
    }

    if (list->length == list->capacity) {
        Triangle *new_data = realloc(list->data, 2 * list->capacity * sizeof(Triangle));

        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }
        list->capacity = list->capacity * 2;
    }

    list->data[list->length] = *tri;

    list->length++;
    return 0;
}

Triangle *tri_list_get(tri_list *list, unsigned int index) {
    if (index > list->length || index <= 0) {
        return NULL;
    }

    return &list->data[index - 1];
}


int tex_list_init(tex_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    
    list->data = malloc(INITIAL_SIZE * sizeof(Texture));
    
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void tex_list_clear(tex_list *list) {
    if (list->capacity == 0) {
        return;
    }

    free(list->data);

    list->length = 0;
    list->capacity = 0;
    list->data = NULL;
}

int tex_list_add(tex_list *list, Texture *tex) {
    if (list->capacity == 0) {
        if (tex_list_init(list) != 0) {
            return -1;
        }
    }

    if (list->length == list->capacity) {
        Texture *new_data = realloc(list->data, 2 * list->capacity * sizeof(Texture));

        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }
        list->capacity = list->capacity * 2;
    }

    list->data[list->length] = *tex;

    list->length++;
    return 0;
}

Texture *tex_list_get(tex_list *list, unsigned int index) {
    if (index > list->length || index <= 0) {
        return NULL;
    }

    return &list->data[index - 1];
}
