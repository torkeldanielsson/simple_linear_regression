# Single-file public-domain (MIT) simple linear regression

[See wikipedia for definition/explanation of simple linear regression.](https://en.wikipedia.org/wiki/Simple_linear_regression)

Library: [simple_linear_regression.h](simple_linear_regression.h)

# Example

A basic usage example, from [example.c](example.c).

```c++
#define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION
#include "simple_linear_regression.h"

#include <stdio.h>

/* Some data that we want to find the slope, intercept and r2 for */
static const double x[] = { 1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83 };
static const double y[] = { 52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46 };

int main() {
    double slope = 0.0;
    double intercept = 0.0;
    double r2 = 0.0;
    double mae = 0.0;
    double mse = 0.0;
    double rmse = 0.0;
    int res = 0;

    res = simple_linear_regression(x, y, sizeof(x) / sizeof(x[0]), &slope, &intercept, &r2, &mae, &mse, &rmse);
    if (res < 0) {
        printf("Error: %s\n", simple_linear_regression_error_string(res));
        return res;
    }

    printf("slope: %f\n", slope);
    printf("intercept: %f\n", intercept);
    printf("r2: %f\n", r2);
    printf("mean average error: %f\n", mae);
    printf("mean square error: %f\n", mse);
    printf("root mean square error: %f\n", rmse);

    return 0;
}
```

# C/C++ standards compliance

This library is tested to compile and run under the following standards: c89 c90 gnu89 gnu90 c99 gnu99 c11 gnu11 c17 gnu17 c++98 c++03 gnu++98 gnu++03 c++11 gnu++11 c++14 gnu++14 c++17 gnu++17 c++2a gnu++2a (see [test.sh](test.sh)).
