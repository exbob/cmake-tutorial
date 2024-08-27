#include <stdio.h>
#include "Config.h"

#ifdef __DEBUG__
    #define pr_debug(format, ...) printf("%s[%04d], %s : "format"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define pr_debug(format, ...)
#endif

int main (int argc, char *argv[])
{
    printf("Project %s, Version %s\n", PROJECT, VERSION);

    pr_debug("debug message\n");
    
    return 0;
}
