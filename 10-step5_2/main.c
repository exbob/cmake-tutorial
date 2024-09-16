#include <stdio.h>
#include <stdlib.h>

#include "Config.h"
#include "libmath.h"

int main(int argc, char *argv[])
{
    double input = 4;
    char *pr;

    if (argc < 2)
    {
        printf("Project %s, Version %s\n", PROJECT, VERSION);
        printf("Usage :\n    %s <number>\n", argv[0]);
        exit(-1);
    }

    input = strtod(argv[1], &pr);

    if (*pr != '\0')
    {
        printf("Error: %s is invalid parameter\n", pr);
        exit(-1);
    }

    double output = mysqrt(input);
    printf("The square root of %f is %f .\n", input, output);

    return 0;
}
