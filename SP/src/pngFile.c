#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <png.h>

// Function to get dimensions of a PNG image
int get_png_dimension(const char *filename, int *width, int *height)
{
    if (!filename && strcmp(filename, ".png") == 0)
    {
        fprintf(stderr, "Error no png file: %s\n", filename);
        return 0;
    }
    
    // Open the PNG file
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 0;
    }

    // Read the PNG file signature
    png_byte header[8];
    fread(header, 1, 8, fp);

    // Check if it's a PNG file
    if (png_sig_cmp(header, 0, 8))
    {
        fclose(fp);
        fprintf(stderr, "Error: %s is not a PNG file.\n", filename);
        return 0;
    }

    // Create PNG read structure
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        fclose(fp);
        fprintf(stderr, "Error creating PNG read structure\n");
        return 0;
    }

    // Create PNG info structure
    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        fclose(fp);
        png_destroy_read_struct(&png, NULL, NULL);
        fprintf(stderr, "Error creating PNG info structure\n");
        return 0;
    }

    // Initialize I/O for PNG file
    png_init_io(png, fp);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    // Get image width and height
    *width = png_get_image_width(png, info);
    *height = png_get_image_height(png, info);

    // Close the file and clean up
    fclose(fp);
    png_destroy_read_struct(&png, &info, NULL);

    return 1;
}

int get_png_pixels(const char *filename)
{
    if (!filename && strcmp(filename, ".png") == 0)
    {
        fprintf(stderr, "Error no png file: %s\n", filename);
        return 0;
    }

    int width, height;
    int px;

    // Call the function to get PNG image dimensions
    if (get_png_dimension(filename, &width, &height))
    {
        // printf("Width: %d, Height: %d\n", width, height);
        px = (unsigned long)width * height;
        // printf("Number of pixels: %d\n", px);
        return px;
    }
    else
    {
        fprintf(stderr, "Failed to get image dimensions.\n");
        return 0;
    }

}
