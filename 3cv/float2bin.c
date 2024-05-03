#include <stdlib.h>
#include <stdio.h>

union float_int
{
    float f;
    unsigned int i;
};

int main(int argc, char *argv[])
{
    union float_int x;
    int i;
    if (argc < 2)
    {
        puts("usage: float2bin <floating-number>\n");
        return EXIT_FAILURE;
    }
    x.f = atof(argv[1]);
    printf("%f(d) = ", x.f);

    for (i = sizeof(x.i) * 8 - 1; i >= 0; --i)
    {
        printf("%c", ((x.i >> i) & 1) + '0');
    }
    printf("(b)\n");

    return EXIT_SUCCESS;
}