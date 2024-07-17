#include <stdio.h>
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