
#ifndef VEC_LIST_H
#define VEC_LIST_H

#include "shapes.h"
#include "vector.h"

typedef struct {
    unsigned int length;      // number of elements in the list
    unsigned int capacity;    // the max size of the list
    Vector **data;            // the list
} vec_list;

/// @brief initializes the list of vectors with 0 length and a capacity of 4
/// @param list the vector list to be initialized
/// @return returns 0 on success and -1 on failure
int vec_list_init(vec_list *list);

/// @brief clears the vector list and frees the memory
/// @param list list to be cleared
void vec_list_clear(vec_list *list);

/// @brief appends a vector at the end of the list. Resizes the list if necessary
/// @param list the list in which the vector gets appended to
/// @param vec vector that gets appended to the list
/// @return returns 0 on success and -1 on failure
int vec_list_add(vec_list *list, Vector *vec);

/// @brief obtains a vector at the given index. Note: this data structure indexes from 1
/// @param list the vector list to index into
/// @param index index of the vector to be obtained
/// @return returns a vector pointer located at the given index
Vector *vec_list_get(vec_list *list, unsigned index);

#endif

#ifndef TRI_LIST_H
#define TRI_LIST_H
typedef struct {
    unsigned int length;      // number of elements in the list
    unsigned int capacity;    // the max size of the list
    Triangle **data;          // the list
} tri_list;

/// @brief initializes the list of triangles with a length of 0 and a capacity of 4
/// @param list a triangle list to be initialized
/// @return returns 0 on success and -1 on failure
int tri_list_init(tri_list *list);

/// @brief clears the triangle list and frees the memory
/// @param list triangle list to be cleared
void tri_list_clear(tri_list *list);

/// @brief appends a Triangle at the end of the list. Resizes the list if necessary
/// @param list the list in which the triangle gets appended to
/// @param tri triangle that gets appended to the list
/// @return return 0 on success and -1 on failure
int tri_list_add(tri_list *list, Triangle *tri);

/// @brief obtains a Triangle at the given index. Note: this data structure indexes from 1
/// @param list the triangle list to index to
/// @param index index of the triangle to be obtained
/// @return returns a Triangle pointer at the given indexes location
Triangle *tri_list_get(tri_list *list, unsigned index);
#endif

#ifndef TEX_LIST_H
#define TEX_LIST_H

typedef struct {
    vec_list **data;    // the texture image
    int height;         // the height of the image
} Texture;

typedef struct {
    unsigned int length;      // number of elements in the list
    unsigned int capacity;    // max size of the list
    Texture **data;           // the list
} tex_list;

/// @brief initializes the list of textures with length of 0 and capacity of 4
/// @param list a list of textures
/// @return returns 0 on success and -1 on failure
int tex_list_init(tex_list *list);

/// @brief clears the list and frees the memory
/// @param list the texture list that needs to be cleared
void tex_list_clear(tex_list *list);

/// @brief adds a texture (an array of vec_lists, which is effectively a 2d array) to the list
/// @param list the list in which the texture gets appended into
/// @param tex the texture that gets appended to the list
/// @return returns 0 on success and -1 on failure
int tex_list_add(tex_list *list, Texture *tex);

/// @brief obtains a Texture at the given index. Note: this data structure indexes from 1
/// @param list the texture list to index into
/// @param index the index of the desired texture
/// @return returns a Texture pointer corresponding to the given index
Texture *tex_list_get(tex_list *list, unsigned index);
#endif
