#include "_test.h"
#include "calculations.h"

using namespace Stopwatch;

TEST(linear_regression_calculates_slope_intercept_and_r_squared) {
    float x[] = {0.0, 1.0, 2.0, 3.0};
    float y[] = {1.0, 3.0, 5.0, 7.0};

    float slope, intercept, rSquared;

    int success = linearRegressionLeastSquares(x, y, 4, slope, intercept, rSquared);

    return success 
        && slope > 1.999 && slope < 2.001
        && intercept > 0.999 && intercept < 1.001
        && rSquared > 0.999 && rSquared < 1.001;
}

TEST(linear_regression_zero_or_one_count_returns_zero) {
    float x[] = {};
    float y[] = {};

    float slope, intercept, rSquared_zero, rSquared_one;

    int success_zero = linearRegressionLeastSquares(x, y, 0, slope, intercept, rSquared_zero);
    int success_one = linearRegressionLeastSquares(x, y, 0, slope, intercept, rSquared_one);

    return !success_zero 
        && rSquared_zero == 0
        && !success_one
        && rSquared_one == 0;
}