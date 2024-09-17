#include <stdio.h>
#include "Config.h"

int main (int argc, char *argv[])
{
    printf("Project %s, Version %s\n", PROJECT, VERSION);

    pr_debug("debug message\n");
    
    return 0;
}
