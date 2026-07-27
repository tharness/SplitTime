#include "_test.h"
#include "actions.h"
#include "data.h"

using namespace Stopwatch;

TEST(rSquared_zero_produces_negative_zone) {
        Data d{
        .position = 0,
    };
    d.models_by_position[0].rSquared = 0;
    stopTimer(d);
    return d.zone < 0;
}

TEST(stopTime_predicts_zone_correctly) {
        Data d{
        .position = 0,
        .split = 3.75
    };
    auto& model = d.models_by_position[0];
    model.rSquared = 0.9426;
    model.slope = -14.8;
    model.intercept = 62.69;
    stopTimer(d);
    return d.zone == 7;
}