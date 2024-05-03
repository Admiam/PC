/**
 * @file pngFile.h
 * @author Adam Míka (mikaa@students.zcu.cz)
 * @brief Header file with function definitions working with png
 * @version 1.0
 * @date 2023-13-11
 */
#ifndef PNG_FILE_H
#define PNG_FILE_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Gets the dimensions of a PNG image.
 *
 * This function opens a PNG file, reads its signature, and retrieves
 * the image width and height
 *
 * @param filename The name of the PNG file
 * @param width A pointer to store the image width
 * @param height A pointer to store the image height
 * @return 1 on success, 0 on failure
 */
int get_png_dimension(const char *filename, int *width, int *height);

/**
 * @brief Calculate number of pixels from PNG image
 *
 * @param filename The name of the PNG file
 * @return number of pixels success, 0 on failure
 */
int get_png_pixels(const char *filename);

#endif
