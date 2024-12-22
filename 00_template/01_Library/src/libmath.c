/*
Copyright (C) 2024 Lishaocheng <https://shaocheng.li>

This program is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License version 3 as published by the Free Software Foundation.
*/
#include <stdio.h>
#include "Config.h"
#include "libmath.h"

// 计算一个浮点数的平方根
double mysqrt(double x) {
    if (x <= 0) {
        return 0;
    }

    double result = x;

    // do ten iterations
    for (int i = 0; i < 10; ++i) {
        if (result <= 0) {
            result = 0.1;
        }
        double delta = x - (result * result);
        result = result + 0.5 * delta / result;
    }
    return result;
}

/*
print version information
*/
void mysqrt_version()
{
    printf("%s, version %s\n", PROJECT, VERSION);
    printf("Commit ID: %s\n", GIT_HASH);
    printf("Commit Data: %s\n", GIT_DATE);
    printf("Build Time: %s UTC\n", BUILD_TIME);
}