#include "vecList.h"

#include <stdlib.h>
#include <string.h>

#include "shapes.h"

#define INITIAL_SIZE 4

int vec_list_init(vec_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    list->data = malloc(INITIAL_SIZE * sizeof(Vector *));
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void vec_list_clear(vec_list *list) {
    if (list->capacity == 0) {
        return;
    }

    for (int i = 0; i < list->length; i++) {
        free(list->data[i]);
    }
    free(list->data);

    list->length = 0;
    list->capacity = 0;
}

int vec_list_add(vec_list *list, Vector *vec) {
    if (list->capacity == 0) {
        if (vec_list_init(list) != 0) {
            return -1;
        }
    }

    // resizes the array when the length of the array is equal to the capacity
    if (list->length == list->capacity) {
        Vector **new_data = realloc(list->data, 2 * list->capacity * sizeof(Vector *));

        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }
        list->capacity = list->capacity * 2;
    }

    // allocates memory for the new Vector
    if ((list->data[list->length] = malloc(sizeof(Vector))) == NULL) {
        printf("couldn't allocate memory in vec_list_add\n");
        return -1;
    }

    // make and store a copy of the vector that gets appended
    if (initialize_vector(list->data[list->length], vec->dx, vec->dy, vec->dz) == -1) {
        printf("vector in vec_list_add contains nan\n");
    }

    list->length++;

    return 0;
}

Vector *vec_list_get(vec_list *list, unsigned int index) {
    if (index > list->length) {
        return NULL;
    }
    if (index <= 0) {
        return NULL;
    }

    return list->data[index - 1];
}

int tri_list_init(tri_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    list->data = malloc(INITIAL_SIZE * sizeof(Triangle *));
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void tri_list_clear(tri_list *list) {
    if (list->capacity == 0) {
        return;
    }

    for (int i = 0; i < list->length; i++) {
        free(list->data[i]);
    }
    free(list->data);

    list->length = 0;
    list->capacity = 0;
}

int tri_list_add(tri_list *list, Triangle *tri) {
    if (list->capacity == 0) {
        if (tri_list_init(list) != 0) {
            return -1;
        }
    }

    // resizes the tri_list when length = capacity
    if (list->length == list->capacity) {
        Triangle **new_data = realloc(list->data, 2 * list->capacity * sizeof(Triangle *));
        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }

        list->capacity = list->capacity * 2;
    }

    if ((list->data[list->length] = malloc(sizeof(Triangle))) == NULL) {
        printf("failed to allocate memory in tri_list_add\n");
        return -1;
    }

    // copies the data of the triangle to the list
    memcpy(list->data[list->length], tri, sizeof(Triangle));

    list->length++;
    return 0;
}

Triangle *tri_list_get(tri_list *list, unsigned int index) {
    if (index > list->length) {
        return NULL;
    }
    if (index <= 0) {
        return NULL;
    }

    return list->data[index - 1];
}

int tex_list_init(tex_list *list) {
    list->length = 0;
    list->capacity = INITIAL_SIZE;
    list->data = malloc(INITIAL_SIZE * sizeof(Vector *));
    if (list->data == NULL) {
        return -1;
    }
    return 0;
}

void tex_list_clear(tex_list *list) {
    if (list->capacity == 0) {
        return;
    }

    for (int i = 0; i < list->length; i++) {
        free(list->data[i]);
    }
    free(list->data);

    list->length = 0;
    list->capacity = 0;
}

int tex_list_add(tex_list *list, Texture *tex) {
    if (list->capacity == 0) {
        if (tex_list_init(list) != 0) {
            return -1;
        }
    }

    if (list->length == list->capacity) {
        Texture **new_data = realloc(list->data, 2 * list->capacity * sizeof(Texture *));
        if (new_data == NULL) {
            return -1;
        } else {
            list->data = new_data;
        }

        list->capacity = list->capacity * 2;
    }

    // this is ok because texture is already malloced
    list->data[list->length] = tex;

    list->length++;

    return 0;
}

Texture *tex_list_get(tex_list *list, unsigned int index) {
    if (index > list->length) {
        return NULL;
    }
    if (index <= 0) {
        return NULL;
    }

    return list->data[index - 1];
}
