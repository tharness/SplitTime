#include "_test.h"
#include "weightedLinearRegressionModel.h"

using namespace Stopwatch;

TEST(weighted_model_prioritizes_recent_points) {
    WeightedLinearRegressionModel model;
    float x[] = {0, 1, 2, 3};
    float y[] = {0, 0, 0, 10};

    model.buildModelFromData(x, y, 4);

    return model.predict(3) > 8.0f;
}
