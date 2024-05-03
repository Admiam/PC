#include <stdio.h>
   const float PI = 3.14;

int main()
{

    *((float *)&PI) = 3.14159;
    printf("%f\n", PI);
    return 0;
}