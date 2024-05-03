#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 4096
#define ASCII_C 256
unsigned short next_code = 256; // Next available LZW code
unsigned short code;
struct Dictionary *dictionary;


void dict_init()
{
    size_t i;
    dictionary = malloc(sizeof(struct Dictionary) * DICTIONARY_SIZE);
    if (!dictionary)
    {
        return;
    }

    for ( i = 0; i < ASCII_C; i++)
    {
        dict[i].prefix = -1;
        dict[i].character = i;
    }
}

// Function to compress data using LZW
void compress_lzw(FILE *input, FILE *output)
{
    dictionary[DICTIONARY_SIZE];        // Dictionary to store codes and characters
    size_t dictionary_size = 256;       // Initial dictionary size with single-character entries
    size_t output_size = 0;             // Size of the compressed output
    unsigned short index_code = 256;     // Next available LZW code
    unsigned short combine, current_code, next_code;
    size_t i;

    dict_init();
    current_code = fgetc(input);


    while((current_code = fgetc(input)) != (unsigned)EOF)
    {
        combine = (current_code << 8) | (unsigned char)input[i];

        if (find(combine) != -1)
        {
            // Sequence found in the dictionary, extend the current sequence
            current_code = code;
        }
        else
        {
            // Output the code for the current sequence's prefix
            // output[output_size++] = current_code;
            write(current_code, index_code);

            if (next_code < DICTIONARY_SIZE)
            {
                // Add the new sequence to the dictionary
                dictionary[code].prefix = current_code;
                dictionary[code].character = input[i];
                next_code++;
            }

            // Start a new sequence with the current character
            current_code = (unsigned char)input[i];
        }
    }

    if (current_code != 0)
    {
        // Output the code for the last sequence
        output[output_size++] = current_code;
    }

    return output_size;
}

int main()
{
    const char *input_file = "text.txt";    // Replace with your input file name
    const char *output_file = "output.txt"; // Replace with your output file name
    size_t compressed_size;
    FILE *output, *input;
    int input_size;
    char *input_data;
    unsigned short *compressed_output;

    // Open the input file
    input = fopen(input_file, "rb");
    output = fopen(output_file, "w");

    if (input == NULL || output == NULL)
    {
        printf("Error opening input file: %s, %s\n", input, output);
        return 1;
    }

    compress_lzw(input, output);

    fclose(input);
    fclose(output); // close handles

    return 0;
}
