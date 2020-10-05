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
 * C test program for simple_linear_regression.h
 *
 * Compile and run using e.g.
 * clang -Wall -Weverything -Wpedantic -Werror test.c && ./a.out
 * gcc -Wall -Wpedantic -Werror test.c && ./a.out
 */

#define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION
#include "simple_linear_regression.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_POINTS (20)
#define TRUE_SLOPE  (1.0)
#define RAND_SCALE  (10.0)

static double random_n1_1() {
    return 2.0 * (double)(rand()) / (double)(RAND_MAX) - 1.0;
}

static int fd_equals(double d, float f) {
    if (fabs(d - (double)(f)) < 0.0001) {
        return 1;
    }
    return 0;
}

int main() {
    int i = 0;
    int res = -1;
    double x[DATA_POINTS] = { 0 };
    double y[DATA_POINTS] = { 0 };
    double i_real = 0.0;
    double slope = 0.0;
    double intercept = 0.0;
    double r2 = 0.0;
    float xf[DATA_POINTS] = { 0 };
    float yf[DATA_POINTS] = { 0 };
    float slopef = 0.0f;
    float interceptf = 0.0f;
    float r2f = 0.0f;

    srand((unsigned int)(time(NULL)));

    printf("Test (C) of simple_linear_regression.h, using random test data:\n\n");

    for (i = 0; i < DATA_POINTS; ++i) {
        i_real = (double)i;
        x[i] = i_real + random_n1_1();
        y[i] = TRUE_SLOPE * i_real + RAND_SCALE * random_n1_1();
        xf[i] = (float)(x[i]);
        yf[i] = (float)(y[i]);

        printf("%f, %f\n", x[i], y[i]);
    }

    res = simple_linear_regression(x, y, DATA_POINTS, &slope, &intercept, &r2);
    if (res < 0) {
        printf("%s\n", simple_linear_regression_error_string(res));
        return res;
    }

    printf("\nslope: %f\n", slope);
    printf("intercept: %f\n", intercept);
    printf("r2: %f\n", r2);

    /* Check that the float version gives the same result */
    res = simple_linear_regressionf(xf, yf, DATA_POINTS, &slopef, &interceptf, &r2f);
    if (res != 0) {
        printf("\nERROR: simple_linear_regressionf mismatch (%d != 0)\n", res);
        return -1;
    }
    if (!fd_equals(slope, slopef)) {
        printf("\nERROR: simple_linear_regressionf mismatch (slope: %f != %f)\n", slope, (double)(slopef));
        return -1;
    }
    if (!fd_equals(intercept, interceptf)) {
        printf("\nERROR: simple_linear_regressionf mismatch (intercept: %f != %f)\n", intercept, (double)(interceptf));
        return -1;
    }
    if (!fd_equals(r2, r2f)) {
        printf("\nERROR: simple_linear_regressionf mismatch (r2: %f != %f)\n", r2, (double)(r2f));
        return -1;
    }

    return 0;
}
