#include "compress.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// gcc src/compress.c -o compress.exe -Wall -Wextra -pedantic -ansi -g 

#define DICTIONARY_SIZE 4096

int left = 0, no_pref = -1, left_bit, compress_count = 0, normal_count= 0, decompress_count = 0;
size_t next_code = 255;
int code;

struct Dictionary *dictionary, *tail;

void list_add(struct Dictionary *node)
{
    if (dictionary != NULL)
    {
        tail->next = node;
    }
    else
    {
        dictionary = node;
    }
    tail = node;
    node->next = NULL;
}

int dict_init()
{
    size_t i;
    struct Dictionary *dict;

    for (i = 0; i < 256; i++)
    {
        // Indicates no prefix
        dict=(struct Dictionary *)malloc(sizeof(struct Dictionary));
        dict->prefix = -1;
        dict->character = i;
        list_add(dict);
    }
    return 1;
}

void dict_deallocate()
{
    while (dictionary != NULL)
    {
        struct Dictionary *tmp = dictionary;
        dictionary = dictionary->next;
        free(tmp);
    }    
}

void write(int *compress_arr[], int code)
{
    if (!compress_arr && code == EOF)
    {
        printf("Error opening output file or code \n");
        return;
    }
    // printf("puvodni %d |", code);

    compress_arr[compress_count] = code;

    printf("pole %d | index %zu \n", compress_arr[compress_count], compress_count);
 
    compress_count += 1;

    // fputc(code, output);
   
}

int find_code(int character, int prefix)
{
    struct Dictionary *code;
    
    for (code = dictionary; code != NULL; code = code->next)
    {
        // printf("Character is %d vs %d\n", character, code->character);
        // printf("Prefix is %d vs %d\n", prefix, code->prefix);

        if (code->character == character && code->prefix == prefix)
        {
            // printf("I found code %d\n", code->character);
            return code->value;
        }
        // code = code->next;
    }
    return -1;
}

int dict_add(int prefix, int character, int value)
{
    if (!prefix && !character && !value)
    {
        printf("Error adding to dictionary\n");
        return 0;
    }

    // printf("Adding to dictionary: %d, %d, %d\n", prefix, character, value);
    
    struct Dictionary *code;
    code = (struct Dictionary *)malloc(sizeof(struct Dictionary));

    code->value = value;
    code->prefix = prefix;
    code->character = character;
    list_add(code);

    // printf("\n(%i) = (%i) + (%i)\n", code->value, code->prefix, code->character);
}

int dictionaryPrefix(int value)
{
    struct Dictionary *node;
    for (node = dictionary; node != NULL; node = node->next)
    {
        if (node->value == value)
            return node->prefix;
    }
    return -1;
}

int dictionaryCharacter(int value)
{
    struct Dictionary *node;
    for (node = dictionary; node != NULL; node = node->next)
    {
        if (node->value == value)
        {
            return node->character;
        }
    }
    return -1;
}

int compress_lzw(FILE *input, int *compress_arr[])
{
    printf("# # # # # # # # # # # # compress # # # # # # # # # # # # # # # # # \n");

    if (input == NULL || compress_arr == NULL)
    {
        printf("Error opening input file and array\n");
        return 0;
    }

    size_t i, x, z;
    // FILE *decomp;
    size_t output_size = 0; // Size of the compressed output
    int isTrue = 0, character, current_code, index, out;
    int prefix = getc(input); 
    normal_count = 1;


    if (prefix == EOF)
    {
        printf("Error reading input file\n");
        return 0;
    }
    // printf(" %d ", prefix);
    
    if (!dict_init())
    {
        printf("Error initializing dictionary\n");
        return 0;
    }


    while ((character = getc(input)) != EOF)
    {
        normal_count += 1;
        // printf(" %d ", character);
        if ((index = find_code(character, prefix)) != -1)
        {
            prefix = index;
            // printf("FindCode was false, prefix is %d\n", prefix);
       }else{
           write(compress_arr, prefix);

           if (next_code < DICTIONARY_SIZE)
           {
               next_code = next_code + 1;
               dict_add(prefix, character, next_code);
            }

            prefix = character;
       }
    }

    write(compress_arr, prefix);

    // if (left > 0)
    // {
    //     fputc(left_bit << 4, output);
    // }
    
    dict_deallocate();
    printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n");
    printf("Normal count: %d\n", normal_count);
    printf("Compress count: %d\n", compress_count);
    printf("# # # # # # # # # # # #  end compress # # # # # # # # # # # # # # #\n");

    return 1;

}

int decompress(FILE *compressFile, int *compress_arr[])
{
    int currentCode, firstChar;
    int nextCode = 256;
    size_t arr = 0;
    int previousCode = compress_arr[arr];
    printf(" # # # # # # # # # # # # #  decompress  # # # # # # # # # # # # # #\n");

    // printf("Compress array: %d\n", compress_arr[arr]);

    if (compressFile == NULL && compress_arr == NULL)
    {
        printf("Error opening compressFile file: \n");
        return 0;
    }

    arr++;

    if (previousCode == 0)
    {
        printf("Error reading compressFile file\n");
        return 0;
    }
    fputc(previousCode, compressFile);
    printf("add %d\n", previousCode);

    while ((currentCode = compress_arr[arr]) != NULL)
    {
        arr++;
        if (currentCode >= nextCode)
        {
            fputc(firstChar = decode(previousCode, compressFile), compressFile);
            printf("add %d\n", firstChar);
        }
        else
            firstChar = decode(currentCode, compressFile);

        if (nextCode < DICTIONARY_SIZE)
            dict_add(previousCode, firstChar, nextCode++);

        previousCode = currentCode;
    }

    dict_deallocate();
    printf("# # # # # # # # # # # # end decompress # # # # # # # # # # # # # # \n");

    return 1;
}

int decode(int code, FILE *compressFile)
{
    if (code == EOF || compressFile == NULL)
    {
        printf("Error opening outputFile file: %s\n", compressFile);
        return 0;
    }


    int character;
    int temp;

    if (code > 255)
    {
        character = dictionaryCharacter(code);
        temp = decode(dictionaryPrefix(code), compressFile);
    }
    else
    {
        character = code;
        temp = code;
    }
    printf("add %d\n", character);
    fputc(character, compressFile);
    return temp;
}
