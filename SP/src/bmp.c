#include "bmp.h"

/* Function to load BMP header from the image file */
int loadBMP(FILE *image, struct BMPHeader *header)
{
    /* Declaration of variables */
    fread(header, sizeof(struct BMPHeader), 1, image);

    /* Check for BMP signature and bits per pixel */
    if (header->signature != BMP_HEADER_SIGNATURE || header->bitsPerPixel != 24)
    {
        return 0; /* Invalid BMP format */
    }

    return 1; /* BMP loaded successfully */
}

/* Function to calculate the total number of pixels in the image */
int getNumberOfPixels(struct BMPHeader imageHeader)
{
    return (imageHeader.height * imageHeader.width);
}

/* Function to hide a message in the BMP image */
void hideMessageInBMP(FILE *image, FILE *binaryMessage)
{
    /* Declaration of variables */
    struct BMPHeader header;
    int byte;
    int extraLength = 16; /* 16 bits added to the image (8 at the beginning, 8 at the end) */
    char *binaryChar;

    /* Check for valid file pointers */
    if (!image || !binaryMessage)
    {
        return;
    }

    /* Check if it's a BMP image */
    if (loadBMP(image, &header) == 0)
    {
        printf("Invalid image format (not 24-bit/pixel RGB BMP)\n");
        return;
    }

    /* Check if the message can fit in the image */
    if ((getNumberOfPixels(header) - extraLength) < (8 * ftell(binaryMessage)))
    {
        printf("Image is not large enough to hide the payload and required information\n");
        return;
    }

    fseek(image, header.dataOffset, SEEK_SET); /* Find the beginning of the image */

    /* Write recognition character */
    writeCharacter(FIRST_AND_LAST_CHAR, image);

    /* Encode the message into the image */
    while ((byte = fgetc(binaryMessage)) != EOF)
    {
        binaryChar = codeToBinary(byte);
        writeCharacter(binaryChar, image);
    }

    writeCharacter(FIRST_AND_LAST_CHAR, image);
}

/* Function to extract a hidden message from the BMP image */
void getMessageFromBMP(FILE *image, FILE *output)
{
    /* Declaration of variables */
    struct BMPHeader header;
    char *character;
    FILE *binaryFileWithMessage = fopen("files/hiddenMessage", "w+b");

    /* Check for valid file pointers */
    if (!image || !output || !binaryFileWithMessage)
    {
        printf("Unable to open files\n");
        return;
    }

    /* Check if it's a BMP image */
    if (!loadBMP(image, &header))
    {
        printf("Invalid image format (not 24-bit/pixel RGB BMP)\n");
        return;
    }

    fseek(image, header.dataOffset, SEEK_SET);

    /* Check if there is anything hidden in the image */
    if (strcmp(character = readCharacter(image), FIRST_AND_LAST_CHAR))
    {
        printf("Image intended for payload extraction does not contain any hidden content\n");
        free(character);
        fclose(binaryFileWithMessage);
        return;
    }

    free(character);

    /* Continue extraction until the end character is found */
    while (strcmp(character = readCharacter(image), FIRST_AND_LAST_CHAR))
    {
        fputc(binaryToCode(character), binaryFileWithMessage);
        free(character);
    }
    free(character);

    fseek(binaryFileWithMessage, 0, SEEK_SET);

    /* Decompress the hiddenMessage file */
    decompress(binaryFileWithMessage, output);

    fclose(binaryFileWithMessage);
}

/* Function to write a binary code into the image */
void writeCharacter(char *binaryCode, FILE *image)
{
    int i;

    /* Check for valid file pointer */
    if (!image)
    {
        return;
    }

    /* Write individual bits into the LSB of the blue channel */
    for (i = 0; i < 8; ++i)
    {
        uint8_t pixel[3];
        fread(&pixel, sizeof(uint8_t), 3, image);
        pixel[0] = (pixel[0] & 0xFE) | (binaryCode[i] - '0');

        fseek(image, -3, SEEK_CUR);
        fwrite(&pixel, sizeof(uint8_t), 3, image);
    }
}

/* Function to read a binary code from the image */
char *readCharacter(FILE *image)
{
    int i;
    char *extractedMessage = (char *)malloc(9);

    /* Check for valid file pointer */
    if (!image)
    {
        return NULL;
    }

    /* Read individual bits from the image */
    for (i = 0; i < 8; ++i)
    {
        uint8_t pixel[3];
        fread(&pixel, sizeof(uint8_t), 3, image);
        extractedMessage[i] = (pixel[0] & 0x01) + '0';
    }

    extractedMessage[8] = '\0';
    return extractedMessage;
}
