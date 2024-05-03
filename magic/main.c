#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARG_COUNT 2
#define DEFAULT_SIZE 1024

void deallocate(int count, int **matrix){
    int i;

    for (i = 0; i < count; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int diagonalValidation(int count, int **matrix){
    int i, diag1 = 0, diag2 = 0;

    printf("count is %d\n", matrix[0][0]);
    for (i = 0; i < count; i++)
    {
        diag1 += matrix[i][i];
    }

    for (i = 0; i < count; i++)
    {
        diag2 += matrix[i][count - 1 - i];
    }

    if (diag1 == diag2)
    {
        printf("Diagonals are equal %d == %d\n", diag1, diag2);
        return diag1;
    }else{
        printf("Diagonals are not equal %d != %d\n", diag1, diag2);
        return 0;
    }
}

int rowValidation(int count, int **matrix, int diag){
    int i, j, sum = 0;

    for (i = 0; i < count; i++)
    {
        sum = 0;
        for (j = 0; j < count; j++)
        {
            sum += matrix[i][j];
        }

        if (sum != diag)
        {
            printf("Row %d is not equal to %d\n", i, diag);
            return 0;
        }else{
            printf("Row %d are equal to  %d == %d\n", i, sum, diag);
        }
    }

    return sum;
    
}

int colValidation(int count, int **matrix, int diag){
    int i, j, sum = 0;

    for (i = 0; i < count; i++)
    {
        sum = 0;
        for (j = 0; j < count; j++)
        {
            sum += matrix[j][i];
        }

        if (sum != diag)
        {
            printf("Col %d is not equal to %d\n", i, diag);
            return 0;
        }else{
            printf("Col %d are equal to  %d == %d\n", i, sum, diag);
        }
    }

    return sum;
    
}

void parseFile(const char *filename){
    char buffer[DEFAULT_SIZE], temp[DEFAULT_SIZE];
    FILE *file;
    char *token;
    int i = 0, size = 0, row = 0, col = 0, swap = EOF, diag = 0, sum = 0;
    int **matrix;

    if (filename == NULL)
    {
        printf("Error: filename is NULL\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(buffer, sizeof(buffer), file))
    {
        if (swap == EOF)
        {    
            memcpy(temp, buffer, sizeof(buffer));

            size = 0;
            token = strtok(buffer, ",");

            while (token != NULL)
            {
                printf("token: %s\n", token);
                token = strtok(NULL, ",");
                size++;
            }

            matrix = (int **) malloc(size * sizeof(int *));

            if (matrix == NULL)
            {
                printf("Error allocating memory\n");
                exit(EXIT_FAILURE);
            }

            for (i = 0; i < size; i++)
            {
                matrix[i] = (int *) malloc(size * sizeof(int));

                if (matrix[i] == NULL)
                {
                    printf("Error allocating memory\n");
                    exit(EXIT_FAILURE);
                }
            }

            memcpy(buffer, temp, sizeof(temp));
            swap = 1;
        }

        token = strtok(buffer, ",");
        while (token != NULL)
        {    
            matrix[row][col] = atoi(token);
            printf("add %d on row: %d | col: %d\n", matrix[row][col], row, col);
            col++;
            token = strtok(NULL, ",");
        }
        row++;
        printf("\n");

        col = 0;
    }

    fclose(file);


    if(!(diag = diagonalValidation(size, matrix))){
        deallocate(size, matrix);
        exit(EXIT_FAILURE);
    }else if (!(sum = rowValidation(size, matrix, diag))){
        deallocate(size, matrix);
        exit(EXIT_FAILURE);
    }else if (!colValidation(size, matrix, diag)){
        deallocate(size, matrix);
        exit(EXIT_FAILURE);
    }
}

int isSupportedFormat(const char *filename)
{
    const char *ext = strrchr(filename, '.');
    if (ext != NULL)
    {
        if (strcmp(ext, ".csv") == 0)
        {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{

    if (argc != ARG_COUNT)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;

    }else if (!isSupportedFormat(argv[1]))
    {
        printf("Error: file format not supported\n");
        return EXIT_FAILURE;
    }
       
    

    parseFile(argv[1]);

    return EXIT_SUCCESS;
}
