#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure representing a dictionary node for LZW compression.
 */
struct Dictionary
{
    int prefix;              /**< Prefix code. */
    int character;           /**< Character code. */
    int value;               /**< LZW code value. */
    struct Dictionary *next; /**< Pointer to the next node in the linked list. */
};

extern int left;              /**< Leftover bits from compression. */
extern int no_pref;           /**< Constant indicating no prefix. */
extern int left_bit;          /**< Leftover bits during reading from input. */
extern int compress_count;    /**< Counter for compressed codes. */
extern int normal_count;      /**< Counter for normal codes. */
extern int decompress_count;  /**< Counter for decompressed codes. */
extern size_t next_code;      /**< Next available LZW code. */
extern int code;              /**< Temporary variable to hold LZW codes. */
// extern int compress_arr[500]; /**< Array to store compressed codes. */

extern struct Dictionary *dictionary; /**< Pointer to the LZW compression dictionary. */
extern struct Dictionary *tail;       /**< Pointer to the tail of the linked list. */

/**
 * @brief Add a node to the end of the linked list.
 * @param node The node to be added.
 */
void list_add(struct Dictionary *node);

/**
 * @brief Initialize the dictionary with default entries.
 * @return 1 if successful, 0 otherwise.
 */
int dict_init();

/**
 * @brief Deallocate memory used by the dictionary.
 */
void dict_deallocate();

/**
 * @brief Write a code to the compression array.
 * @param compress_arr The compression array.
 * @param code The code to be written.
 */
void write(int *compress_arr[], int code);

/**
 * @brief Find a code in the dictionary.
 * @param character The character to be found.
 * @param prefix The prefix to be found.
 * @return The code if found, -1 otherwise.
 */
int find_code(int character, int prefix);

/**
 * @brief Add an entry to the dictionary.
 * @param prefix The prefix of the entry.
 * @param character The character of the entry.
 * @param value The value of the entry.
 * @return 1 if successful, 0 otherwise.
 */
int dict_add(int prefix, int character, int value);

/**
 * @brief Get the prefix of a value in the dictionary.
 * @param value The value to find in the dictionary.
 * @return The prefix if found, -1 otherwise.
 */
int dictionaryPrefix(int value);

/**
 * @brief Get the character of a value in the dictionary.
 * @param value The value to find in the dictionary.
 * @return The character if found, -1 otherwise.
 */
int dictionaryCharacter(int value);

/**
 * @brief Compress input using LZW algorithm.
 * @param input The input file.
 * @param compress_arr The compression array.
 * @return 1 if successful, 0 otherwise.
 */
int compress_lzw(FILE *input, int *compress_arr[]);

/**
 * @brief Decompress the compressed file.
 * @param compressFile The compressed file.
 * @return 1 if successful, 0 otherwise.
 */
int decompress(FILE *compressFile, int *compress_arr[]);

/**
 * @brief Decode a code and write to the output file.
 * @param code The code to be decoded.
 * @param outputFile The output file.
 * @return The decoded character.
 */
int decode(int code, FILE *outputFile);

#endif /* COMPRESS_H */