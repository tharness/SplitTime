#include "_test.h"
#include "calculations.h"

using namespace Stopwatch;

TEST(linear_regression_calculates_slope_intercept_and_r_squared) {
    float x[] = {0.0, 1.0, 2.0, 3.0};
    float y[] = {1.0, 3.0, 5.0, 7.0};

    float slope, intercept, rSquared;

    linearRegressionLeastSquares(x, y, 4, slope, intercept, rSquared);

    return rSquared > 0 
        && slope > 1.999 && slope < 2.001
        && intercept > 0.999 && intercept < 1.001
        && rSquared > 0.999 && rSquared < 1.001;
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