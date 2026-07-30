#include "_test.h"
#include "actions.h"
#include "data.h"

using namespace Stopwatch;

TEST(rSquared_zero_produces_negative_zone) {
        Data d{
        .position = 0,
    };
    d.models_by_position[0].rSquared = 0;
    predictZone(d);
    return d.zone < 0;
}

TEST(predictZone_predicts_zone_correctly) {
        Data d{
        .position = 0,
        .split = 3.75
    };
    auto& model = d.models_by_position[0];
    // y = -14.8x + 62.69
    // r^2 = 0.9426
    model.rSquared = 0.9426;
    model.slope = -14.8;
    model.intercept = 62.69;
    predictZone(d);
    return d.zone == 7;
}

TEST(predictZone_hog_produces_zone_zero) {
        Data d{
        .position = 0,
        .split = 5.0
    };
    auto& model = d.models_by_position[0];
    // y = -14.8x + 62.69
    // r^2 = 0.9426
    model.rSquared = 0.9426;
    model.slope = -14.8;
    model.intercept = 62.69;
    predictZone(d);
    return d.zone == 0;
}

TEST(predictZone_through_produces_zone_eleven) {
        Data d{
        .position = 0,
        .split = 2.0
    };
    auto& model = d.models_by_position[0];
    // y = -14.8x + 62.69
    // r^2 = 0.9426
    model.rSquared = 0.9426;
    model.slope = -14.8;
    model.intercept = 62.69;
    predictZone(d);
    return d.zone ==11;
}