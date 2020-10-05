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

#ifndef SIMPLE_LINEAR_REGRESSION_H
#define SIMPLE_LINEAR_REGRESSION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Simple linear regression, as described on wikipedia:
 * https://en.wikipedia.org/wiki/Simple_linear_regression
 * 
 * x and y must point to contiguous arrays with n elements
 * _out parameters may be NULL
 * returns: 0 on success or < 0 on error, see below for error codes
 */
int simple_linear_regression(const double * x, const double * y, const int n, double * slope_out, double * intercept_out, double * r2_out);
int simple_linear_regressionf(const float * x, const float * y, const int n, float * slope_out, float * intercept_out, float * r2_out);

/* Error codes */
#define SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE -2
#define SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC     -3

/* Returns pointer to string representation of error (pointer to static data, must not be freed) */
const char * simple_linear_regression_error_string(int error);

/* 
 * To include implementation code define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION before including simple_linear_regression.h.
 * 
 * E.g. create a file called simple_linear_regression.c with the following contents:
 * #define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION 
 * #include "simple_linear_regression.h"
 * (This is useful in larger codebases, for smaller codebases do like in the example and define before include in a .c/.cpp file)
 */
#ifdef SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION

int simple_linear_regression(const double * x, const double * y, const int n, double * slope_out, double * intercept_out, double * r2_out) {
    double sum_x = 0.0;
    double sum_xx = 0.0;
    double sum_xy = 0.0;
    double sum_y = 0.0;
    double sum_yy = 0.0;
    double n_real = (double)(n);
    int i = 0;
    double slope = 0.0;
    double denominator = 0.0;

    if (x == NULL || y == NULL || n < 2) {
        return SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE;
    }

    for (i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
        sum_y += y[i];
        sum_yy += y[i] * y[i];
    }

    denominator = n_real * sum_xx - sum_x * sum_x;
    if (denominator == 0.0) {
        return SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC;
    }
    slope = (n_real * sum_xy - sum_x * sum_y) / denominator;

    if (slope_out != NULL) {
        *slope_out = slope;
    }

    if (intercept_out != NULL) {
        *intercept_out = (sum_y  - slope * sum_x) / n_real;
    }

    if (r2_out != NULL) {
        denominator = ((n_real * sum_xx) - (sum_x * sum_x)) * ((n_real * sum_yy) - (sum_y * sum_y));
        if (denominator == 0.0) {
            return SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC;
        }
        *r2_out = ((n_real * sum_xy) - (sum_x * sum_y)) * ((n_real * sum_xy) - (sum_x * sum_y)) / denominator;
    }

    return 0;
}

int simple_linear_regressionf(const float * x, const float * y, const int n, float * slope_out, float * intercept_out, float * r2_out) {
    float sum_x = 0.0f;
    float sum_xx = 0.0f;
    float sum_xy = 0.0f;
    float sum_y = 0.0f;
    float sum_yy = 0.0f;
    float n_real = (float)(n);
    int i = 0;
    float slope = 0.0f;
    float denominator = 0.0f;

    if (x == NULL || y == NULL || n < 2) {
        return SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE;
    }

    for (i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_xx += x[i] * x[i];
        sum_xy += x[i] * y[i];
        sum_y += y[i];
        sum_yy += y[i] * y[i];
    }

    denominator = n_real * sum_xx - sum_x * sum_x;
    if (denominator == 0.0f) {
        return SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC;
    }
    slope = (n_real * sum_xy - sum_x * sum_y) / denominator;

    if (slope_out != NULL) {
        *slope_out = slope;
    }

    if (intercept_out != NULL) {
        *intercept_out = (sum_y  - slope * sum_x) / n_real;
    }

    if (r2_out != NULL) {
        denominator = ((n_real * sum_xx) - (sum_x * sum_x)) * ((n_real * sum_yy) - (sum_y * sum_y));
        if (denominator == 0.0f) {
            return SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC;
        }
        *r2_out = ((n_real * sum_xy) - (sum_x * sum_y)) * ((n_real * sum_xy) - (sum_x * sum_y)) / denominator;
    }

    return 0;
}

const char * simple_linear_regression_error_string(int error) {
    if (error == SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE) {
        return "SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE";
    }
    if (error == SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC) {
        return "SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC";
    }
    return "SIMPLE_LINEAR_REGRESSION: Unknown error";
}

#endif /* SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif

#endif /* SIMPLE_LINEAR_REGRESSION_H */
