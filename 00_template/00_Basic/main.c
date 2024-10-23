#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "Config.h"

int main(int argc, char *argv[])
{
    printf("Project %s, Version %s, Build time %s UTC\n", PROJECT, VERSION, BUILD_TIME);
    printf("Commit: %s, Date: %s\n", GIT_HASH, GIT_DATE);

    pr_info("info message\n");
    pr_error("%d: %s", errno, strerror(errno));
    pr_debug("debug message\n");

    return 0;
}
