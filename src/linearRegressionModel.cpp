#include "linearRegressionModel.h"

namespace Stopwatch {

void LinearRegressionModel::buildModelFromData(const float* x, const float* y, int count) {
    if (count <= 1) {
        rSquared = 0;
        return;
    }

    float sumX = 0.0;
    float sumY = 0.0;
    float sumXX = 0.0;
    float sumXY = 0.0;

    for (int i = 0; i < count; ++i) {
        sumX += x[i];
        sumY +=y[i];
        sumXX += x[i] * x[i];
        sumXY += x[i] * y[i];
    }

    float denominator = (count * sumXX) - (sumX * sumX);

    if (denominator == 0.0) {
        rSquared = 0;
        return;
    }

    slope = ((count * sumXY) - (sumX * sumY)) / denominator;
    intercept = (sumY - (slope * sumX)) / count;

    float meanX = sumX / count;
    float meanY = sumY / count;
    float ssTot = 0.0;
    float ssRes = 0.0;

    for (int i = 0; i < count; ++i) {
        float fitted = (slope * x[i]) + intercept;
        float diff = y[i] - meanY;
        float resid = y[i] - fitted;
        ssTot += diff * diff;
        ssRes += resid * resid;
    }

    if (ssTot == 0.0) {
        rSquared = 1.0;
    } else {
        rSquared = 1.0 - (ssRes / ssTot);
    }

    return;
}

float LinearRegressionModel::predict(float x) {
    return slope * x + intercept;
}

float LinearRegressionModel::predictInverse(float y) {
    if (slope == 0) return 0;
    return (y - intercept) / slope;
}

float LinearRegressionModel::getConfidence() {
    return rSquared;
}

}