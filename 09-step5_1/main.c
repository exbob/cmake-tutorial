#include <stdio.h>
#include "Config.h"
#include "libmath.h"

int main(int argc, char *argv[])
{
    printf("Project %s, Version %s\n", PROJECT, VERSION);

    double input = 4;
    double output = mysqrt(input);
    printf("The square root of %f is %f .\n", input, output);

    return 0;
}
