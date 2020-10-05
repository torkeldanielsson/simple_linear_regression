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

// C++ test program for simple_linear_regression.h
//
// Compile and run using e.g.
// clang++ -Wall -Weverything -Wpedantic -Werror test.cpp && ./a.out
// g++ -Wall -Wpedantic -Werror test.cpp && ./a.out

// NULL and old-style-cast are used for compatibility with C and c++98
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#define SIMPLE_LINEAR_REGRESSION_IMPLEMENTATION
#include "simple_linear_regression.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

static const int DataPoints = 20;
static const double TrueSlope = 1.0;
static const double RandScale = 10.0;

static double random_n1_1() {
    return 2.0 * static_cast<double>(rand()) / static_cast<double>(RAND_MAX) - 1.0;
}

static int fd_equals(double d, float f) {
    if (fabs(d - static_cast<double>(f)) < 0.0001) {
        return 1;
    }
    return 0;
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    std::cout << "Test (C++) of simple_linear_regression.h, using random test data:" << std::endl << std::endl;

    std::vector<double> x;
    std::vector<double> y;
    std::vector<float> xf;
    std::vector<float> yf;

    for (int i = 0; i < DataPoints; ++i) {
        double i_real = static_cast<double>(i);
        x.push_back(i_real + random_n1_1());
        y.push_back(TrueSlope * i_real + RandScale * random_n1_1());

        xf.push_back(static_cast<float>(x.back()));
        yf.push_back(static_cast<float>(y.back()));

        std::cout << x.back() << ", " << y.back() << std::endl;
    }

    double slope = 0.0;
    double intercept = 0.0;
    double r2 = 0.0;

    int res = simple_linear_regression(x.data(), y.data(), DataPoints, &slope, &intercept, &r2);
    if (res < 0) {
        std::cerr << simple_linear_regression_error_string(res) << std::endl;
        return res;
    }

    std::cout << std::endl << "slope: " << slope << std::endl;
    std::cout << "intercept: " << intercept << std::endl;
    std::cout << "r2: " << r2 << std::endl;

    float slopef = 0.0f;
    float interceptf = 0.0f;
    float r2f = 0.0f;

    /* Check that the float version gives the same result */
    res = simple_linear_regressionf(xf.data(), yf.data(), DataPoints, &slopef, &interceptf, &r2f);
    if (res != 0) {
        std::cerr << "ERROR: simple_linear_regressionf mismatch (" << res << " != 0)" << std::endl;
        return -1;
    }
    if (!fd_equals(slope, slopef)) {
        std::cerr << "ERROR: simple_linear_regressionf mismatch (slope: " << slope << " != " << slopef << ")" << std::endl;
        return -1;
    }
    if (!fd_equals(intercept, interceptf)) {
        std::cerr << "ERROR: simple_linear_regressionf mismatch (intercept: " << intercept << " != " << interceptf << ")" << std::endl;
        return -1;
    }
    if (!fd_equals(r2, r2f)) {
        std::cerr << "ERROR: simple_linear_regressionf mismatch (r2: " << r2 << " != " << r2f << ")" << std::endl;
        return -1;
    }

    return 0;
}
