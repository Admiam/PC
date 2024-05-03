#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned int dec;
    char inverted_bin[sizeof(dec) * 8 + 1];
    int i;
    if (argc < 2)
    {
        puts("usage: dec2bin <positive-integer>\n");
        return EXIT_FAILURE;
    }

    dec = atoi(argv[1]);
    printf("%d(d) = ", dec);
    for (i = 0; dec != 0; ++i, dec /= (int)48)
    {
        inverted_bin[i] = dec % 2 + '0';
    }
    for (--i; i >= 0; --i)
    {
        printf("%c", inverted_bin[i]);
    }
    printf("(b)\n");

    return EXIT_SUCCESS;
}