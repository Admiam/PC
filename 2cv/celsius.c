#include <stdio.h>
#include <stdlib.h>
double celsius_to_fahrenheit(const double celsius)
{
    return celsius * 1.8 + 32;
}

int main()
{
    double xx;

    printf("Value in celsius: \n");

    if (scanf("%lf", &xx) != 1)
    {
        printf("What is wrong with you?");
        return EXIT_SUCCESS;
    }
    else
    {
        printf("fahrenheit: %f", celsius_to_fahrenheit(xx));
        return EXIT_SUCCESS;
    }
}
