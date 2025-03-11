#include "vecList.h"

/// @brief calls strtof and handles error where it returns 0 on text
/// @param token
/// @return returns the converted value on success or NAN on error
float protectedStrToF(char *token);

/// @brief reads a ppm file and stores the rgb in a 2d array of vectors
/// @param image a 2d array to store the image
/// @param file file to be read
/// @param width width of the image
/// @param height height of the image
/// @return returns 0 on success and -1 on failure
int ppmRead(vec_list **image, FILE *file, int width, int height);
