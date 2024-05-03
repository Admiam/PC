/*
gcc helloworld.c - o helloworld - Wall - Wextra - pedantic - ansi
echo $?
./helloworld
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{

    printf("Hello world!");

    return EXIT_SUCCESS;
}
