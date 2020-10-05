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

// C++ example for simple_linear_regression.h
//
// Compile and run using e.g.
// clang++ -Wall -Weverything -Wpedantic -Werror example.cpp && ./a.out
// g++ -Wall -Wpedantic -Werror example.cpp && ./a.out

// NULL and old-style-cast are used for compatibility with C and c++98
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION
#include "simple_linear_regression.h"

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#include <iostream>

// Some data that we want to find the slope, intercept and r2 for:
const double x[] = { 1.47, 1.50, 1.52, 1.55, 1.57, 1.60, 1.63, 1.65, 1.68, 1.70, 1.73, 1.75, 1.78, 1.80, 1.83 };
const double y[] = { 52.21, 53.12, 54.48, 55.84, 57.20, 58.57, 59.93, 61.29, 63.11, 64.47, 66.28, 68.10, 69.92, 72.19, 74.46 };

int main() {
    double slope = 0.0;
    double intercept = 0.0;
    double r2 = 0.0;

    int res = simple_linear_regression(x, y, sizeof(x)/sizeof(x[0]), &slope, &intercept, &r2);

    if (res == SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE) {
        std::cerr << "SIMPLE_LINEAR_REGRESSION_ERROR_INPUT_VALUE" << std::endl;
        return res;
    }
    if (res == SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC) {
        std::cerr << "SIMPLE_LINEAR_REGRESSION_ERROR_NUMERIC" << std::endl;
        return res;
    }
    if (res < 0) {
        std::cerr << "Unknown error" << std::endl;
        return res;
    }

    std::cout << "slope: " << slope << std::endl;
    std::cout << "intercept: " << intercept << std::endl;
    std::cout << "r2: " << r2 << std::endl;

    return 0;
}
