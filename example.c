/*
 * MIT License
 *
 * Copyright (c) 2020 Torkel Danielsson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * C example for simple_linear_regression.h
 *
 * Compile and run using e.g.
 * clang -Wall -Weverything -Wpedantic -Werror -lm example.c && ./a.out
 * gcc -Wall -Wpedantic -Werror example.c -lm && ./a.out
 * cl.exe example.c && example.exe
 */

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
