#include "_test.h"
#include "actions.h"
#include "data.h"

using namespace Stopwatch;

TEST(rSquared_zero_produces_zero_split) {
        Data d{
        .position = 0,
    };
    d.models_by_position[0].rSquared = 0;
    enterSplitPredict(d);
    return d.split == 0;
}

TEST(enterSplitPredict_predicts_split_correctly) {
        Data d{
        .position = 0,
        .zone = 7
    };
    auto& model = d.models_by_position[0];
    // y = -14.8x + 62.69
    // x = (y - 62.69) / -14.8
    // r^2 = 0.9426
    model.rSquared = 0.9426;
    model.slope = -14.8;
    model.intercept = 62.69;
    enterSplitPredict(d);
    return d.split > 3.761 && d.split < 3.763;
}