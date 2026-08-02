#include "weightedLinearRegressionModel.h"

namespace Stopwatch {

float pow(float x, int y) {
    float result = 1;
    for(int i = 0; i < y; ++i) {
        result *= x;
    }
    return result;
}

float getWeight(int index, int count) {
    const float WEIGHT_BASE = 0.5f;
    return pow(WEIGHT_BASE, (count - 1 - index));
}

void WeightedLinearRegressionModel::buildModelFromData(const float* x, const float* y, int count) {
    if (count <= 1) {
        rSquared = 0;
        return;
    }

    float sumW = 0.0f;
    float sumWX = 0.0f;
    float sumWY = 0.0f;
    float sumWXX = 0.0f;
    float sumWXY = 0.0f;

    for (int i = 0; i < count; ++i) {
        float weight = getWeight(i, count);
        sumW += weight;
        sumWX += weight * x[i];
        sumWY += weight * y[i];
        sumWXX += weight * x[i] * x[i];
        sumWXY += weight * x[i] * y[i];
    }

    float denominator = (sumW * sumWXX) - (sumWX * sumWX);

    if (denominator == 0.0f) {
        rSquared = 0;
        return;
    }

    slope = ((sumW * sumWXY) - (sumWX * sumWY)) / denominator;
    intercept = (sumWY - (slope * sumWX)) / sumW;

    float weightedMeanX = sumWX / sumW;
    float weightedMeanY = sumWY / sumW;
    float ssTot = 0.0f;
    float ssRes = 0.0f;

    for (int i = 0; i < count; ++i) {
        float weight = getWeight(i, count);
        float fitted = (slope * x[i]) + intercept;
        float diff = y[i] - weightedMeanY;
        float resid = y[i] - fitted;
        ssTot += weight * diff * diff;
        ssRes += weight * resid * resid;
    }

    if (ssTot == 0.0f) {
        rSquared = 1.0f;
    } else {
        rSquared = 1.0f - (ssRes / ssTot);
    }
}

float WeightedLinearRegressionModel::predict(float x) {
    return slope * x + intercept;
}

float WeightedLinearRegressionModel::predictInverse(float y) {
    if (slope == 0) return 0;
    return (y - intercept) / slope;
}

float WeightedLinearRegressionModel::getConfidence() {
    return rSquared;
}

}