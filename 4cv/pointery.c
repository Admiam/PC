#include <stdlib.h>
#include <stdio.h>

int main()
{
    int cislo;
    int *pointer_na_cislo;
    int **pointer_na_pointer_na_cislo;

    cislo = 5;
    pointer_na_cislo = &cislo;
    pointer_na_pointer_na_cislo = &pointer_na_cislo;

    /*
    pointer = &5  - doesn't work because 5 is value
    pointer_na_cislo - address to stack where is cislo
    pointer_na_cislo - has 4 bytes because it is int
    max 3 stars
    if i can make const (const int cislo)
    const int *pointer - can change address but not value on address
    const int const * pointer - can not change address and value
    */

    printf("%d, %d, %d\n", cislo, *pointer_na_cislo, **pointer_na_pointer_na_cislo);

    return EXIT_SUCCESS;
}
