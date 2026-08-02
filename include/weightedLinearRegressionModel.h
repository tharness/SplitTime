#ifndef WEIGHTED_LINEAR_REGRESSION_MODEL_H
#define WEIGHTED_LINEAR_REGRESSION_MODEL_H

#include "model.h"

namespace Stopwatch {

class WeightedLinearRegressionModel : public Model {
public:
    void buildModelFromData(const float* x, const float* y, int count) override;
    float predict(float x) override;
    float predictInverse(float y) override;
    float getConfidence() override;
private:
    float slope = 0;
    float intercept = 0;
    float rSquared = 0;
};

}

#endif // WEIGHTED_LINEAR_REGRESSION_MODEL_H