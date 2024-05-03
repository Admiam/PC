#include <stdio.h>
#include <stdlib.h>

#define INPUT_MAX_LENGTH 4
int main()
{
    char input[INPUT_MAX_LENGTH] = {0};

    printf("> ");
    fgets(input, INPUT_MAX_LENGTH, stdin);
    printf("given string: + \"%s\"\n", input);

    return EXIT_SUCCESS;
}
