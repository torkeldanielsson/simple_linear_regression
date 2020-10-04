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
 * Test program for simple_linear_regression.h
 *
 * Compile and run using e.g.
 * clang -Wall -Weverything -Werror test.c && ./a.out
 */

#include "simple_linear_regression.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_POINTS (20)
#define TRUE_SLOPE (1.0)
#define RAND_SCALE (10.0)

static double random_n1_1() {
    return 2.0 * (double)(rand()) / (double)(RAND_MAX) - 1.0;
}

int main() {
    double x[DATA_POINTS] = { 0 };
    double y[DATA_POINTS] = { 0 };
    double i_real = 0.0;
    int i = 0;
    int res = -1;

    double slope = 0.0;
    double intercept = 0.0;

    srand((unsigned int)(time(NULL)));

    printf("Test of simple_linear_regression.h, generating random test data:\n");

    for (i = 0; i < DATA_POINTS; ++i) {
        i_real = (double)i;
        x[i] = TRUE_SLOPE * i_real + random_n1_1();
        y[i] = i_real + RAND_SCALE * random_n1_1();

        printf("%f, %f\n", x[i], y[i]);
    }

    res = simple_linear_regression(x, y, DATA_POINTS, &slope, &intercept, NULL);

    if (res == SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE) {
        printf("SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE\n");
        return res;
    }
    if (res == SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC) {
        printf("SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC\n");
        return res;
    }
    if (res < 0) {
        printf("Unknown error\n");
        return res;
    }

    printf("\nslope: %f\n", slope);
    printf("intercept: %f\n", intercept);
    
    return 0;
}
