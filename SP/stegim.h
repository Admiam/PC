/**
 * @file stegim.h
 * @author Adam Míka (mikaa@students.zcu.cz)
 * @brief Header file with function definitions working with file compression
 * @version 1.0
 * @date 2023-12-11
 */

#ifndef STEGIM_H
#define STEGIM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure to hold payload data and its size
 */
typedef struct
{
    char *data;  /**< Pointer to the payload data */
    size_t size; /**< Size of the payload data */
} Payload;

/**
 * @brief Check if the image format is supported (BMP or PNG)
 *
 * @param filename The name of the image file
 * @return 1 if the format is supported, 0 otherwise
 */
int is_supported_format(const char *filename);

/**
 * @brief Hides the payload into the image
 *
 * @param image_filename  The name of the image file
 * @param payload_filename  The name of the payload file
 */
void hide_payload(const char *image_filename, const char *payload_filename);

/**
 * @brief Compress payload with lossless compression
 *
 * @param image_filename  The name of the image file
 * @param payload_filename  The name of the payload file
 */
void compress_payload(const char *image_filename, const char *payload_filename);

/**
 * @brief Verify that the image has the required number of pixels to hide the payload
 *
 * @param n_pix  Number of pixels
 * @param l_comp  Length of compressed content
 * @return 1 if image has the required number of pixels, 3 otherwise
 */
int can_hide(size_t n_pix, size_t l_comp);

/**
 * @brief Hide payload to LSB
 *
 */
void LSB_hide();

/**
 * @brief Save image to disk
 *
 */
void save();

/**
 * @brief Extracts the payload from the image
 *
 * @param image_filename  The name of the image file
 * @param payload_filename  The name of the payload file
 */
void extract_payload(const char *image_filename, const char *payload_filename);

/**
 * @brief Verify if the image has payload
 *
 * @param image_filename  The name of the image file
 * @return 1 if image has payload, 4 otherwise
 */
int is_payload(const char *image_filename);

/**
 * @brief Extract payload from LSB blue
 *
 */
void LSB_extract();

/**
 * @brief Verify if payload is not damaged
 *
 * @param image_filename  The name of the image file
 * @return 1 if payload is not damaged, 5 otherwise
 */
int is_ok(const char *image_filename);

/**
 * @brief Decompress payload
 *
 * @param payload_filename  The name of the payload file
 */
void decompress_payload(const char *payload_filename);

#endif
