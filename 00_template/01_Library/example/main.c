#include <stdio.h>
#include "libmath.h"

int main(int argc, char *argv[])
{
    double input = 4;
    double output = mysqrt(input);
    printf("The square root of %f is %f .\n", input, output);

    printf("\n");
    printf("Base on:\n");
    mysqrt_version();
    
    return 0;
}
