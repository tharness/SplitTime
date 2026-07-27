#include "_test.h"
#include "calculations.h"

using namespace Stopwatch;

TEST(linear_regression_calculates_slope_intercept_and_r_squared) {
    float x[] = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float y[] = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};

    float slope, intercept, rSquared;

    linearRegressionLeastSquares(x, y, sizeof(x)/sizeof(float), slope, intercept, rSquared);

    // y = -14.8x + 62.69
    // r^2 = 0.9426

    return rSquared > 0 
        && slope > -14.9 && slope < -14.7
        && intercept > 62.68 && intercept < 62.70
        && rSquared > 0.9425 && rSquared < 0.9427;
}

TEST(linear_regression_zero_or_one_count_returns_zero) {
    float x[] = {};
    float y[] = {};

    float slope, intercept, rSquared_zero, rSquared_one;

    linearRegressionLeastSquares(x, y, 0, slope, intercept, rSquared_zero);
    linearRegressionLeastSquares(x, y, 0, slope, intercept, rSquared_one);

    return rSquared_zero == 0
        && rSquared_one == 0;
}