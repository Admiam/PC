#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/pngFile.h"
#include "src/bmp.h"
#include "src/compress.h"
// gcc stegim.c src/pngFile.c -o stegim.exe -Wall -Wextra -pedantic -ansi -g -lpng -L/opt/homebrew/lib -I/opt/homebrew/include

typedef struct
{
    char *data;
    size_t size;
} Payload;

int is_supported_format(const char *filename)
{
    // Zkontroluje, zda je formát BMP nebo PNG
    const char *ext = strrchr(filename, '.');
    if (ext != NULL)
    {
        if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".png") == 0)
        {
            return 1;
        }
    }
    return 0;
}

void hide_payload(const char *image_filename, const char *payload_filename)
{
    int width, height;
    FILE *output, *input, *deco;
    const int n_px = get_png_pixels(image_filename);
    const char *output_file = "output.lzw";
    const char *decompress_file = "decompress.txt";
    int character;
    size_t count = 0;


    input = fopen(payload_filename, "r");

    while ((character = getc(input)) != EOF)
    {
        count++;
    }

    fclose(input);


    int *compress_arr = (int *)malloc(count * sizeof(int));

    if (!image_filename || !payload_filename)
    {
        printf("Error image_filename and payload_filename: %s, %s\n", image_filename, payload_filename);
        return;
    }

    input = fopen(payload_filename, "r");
    output = fopen(output_file, "w+b");
    deco = fopen(decompress_file, "w+b");

    if (input == NULL || output == NULL || deco == NULL)
    {
        printf("Error opening input, output and decompress file: %s, %s\n", input, output);
        return;
    }

    if (n_px)
    {
        // printf("Success> %d\n", n_px);
    }else{
        fprintf(stderr, "Error number of pixels: %s\n", n_px);
    }

    if (!compress_lzw(input, compress_arr))
    {
        printf("Error compressing payload \n");
        return;
    }


    if (!decompress(deco, compress_arr))
    {
        printf("Error decompressing payload \n");
        return;
    }
    
    // printf("output is %d\n", compress_count);
    fclose(deco);
    fclose(input);
    fclose(output);
    free(compress_arr);

    // Zde implementujte skrývání payloadu do obrázku
    // Pomocí knihovny pro práci s obrázky můžete otevřít obrázek, provést kompresi payloadu a uložit do obrázku
}

int can_hide(size_t n_pix)
{
    if (n_pix >= (8 * compress_count))
    {
        return 1;
    }
    return 3;
}

void LSB_hide()
{
    // TODO ukryt bit po bitu do LSB (nejmene vyznamneho bitu) mohdre slozky pixelu obrazku
}

void save()
{
    // TODO ulozit obrazek ve stejnem fomatu ve kterem byl nacten
}

void extract_payload(const char *image_filename, const char *payload_filename)
{
    // Zde implementujte extrakci payloadu z obrázku
    // Pomocí knihovny pro práci s obrázky můžete otevřít obrázek, extrahovat payload a uložit do souboru
}

int is_payload(const char *image_filename)
{
    // TODO zjistit jestli je v obrazku ukryt payload
    if (image_filename)
    {
        /* code */
        return 1;
    }
    return 4;
}

void LSB_extract()
{
    // TODO vyjmout bit po bitu z LSB modre slozky pixelu obrazku zkomprimovany payload
}

int is_ok(const char *image_filename)
{
    // TODO zjistit jestli payload neni poskozeny
    // vypocet kontrolniho souctu CRC32 a porovnani s ulozenou hodnotou

    if (image_filename)
    {
        /* code */
        return 1;
    }
    return 5;
}

void decompress_payload(const char *payload_filename)
{
    // TODO dekoprimovat payload a ulozit do souboru predaneho 3. parametrem
}

int main(int argc, char *argv[])
{
    size_t i;
    const char *image_filename;
    const char *payload_filename;
    const char *direction;

    if (argc != 4)
    {
        printf("Usage: stegim.exe <image.png|image.bmp> <-h or -x> <payload_file>\n");
        return 1;
    }

    for (i = 1; i < 4; i++)
    {
        if (strcmp(argv[i], "-h") != 0 && strcmp(argv[i], "-x") != 0 )
        {
            if (strcmp(image_filename, payload_filename) != 0)
            {
                image_filename = argv[i];
            }
            payload_filename = argv[i];
        } 
        else 
        {
            direction = argv[i];
        }
    }

    // printf("image: %s\n", image_filename);
    // printf("payload: %s\n", payload_filename);
    // printf("direction: %s\n", direction);

    if (!is_supported_format(image_filename))
    {
        printf("Unsupported image format. Use BMP or PNG.\n");
        return 2;
    }

    if (strcmp(direction, "-h") == 0)
    {
        hide_payload(image_filename, payload_filename);
        // printf("Payload hidden successfully.\n");
    }
    else if (strcmp(direction, "-x") == 0)
    {
        extract_payload(image_filename, payload_filename);
        printf("Payload extracted successfully.\n");
    }
    else
    {
        printf("Invalid direction parameter. Use -h or -x.\n");
        return 1;
    }

    return 0;
}
