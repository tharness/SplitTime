#include "_test.h"
#include "actions.h"
#include "data.h"
#include "linearRegressionModel.h"

using namespace Stopwatch;

TEST(rSquared_zero_produces_negative_zone) {
        Data d{
        .position = 0,
    };
    d.predictor_by_position[0].confidence = 0;
    predictZone(d);
    return d.zone < 0;
}

TEST(predictZone_predicts_zone_correctly) {
    Data d{
        .position = 0
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    // save shots for a single player
    int count = 10;
    float splits[]  = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[]   = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        addShot(d);
    }

    // known correct answer
    d.split = 3.75;
    predictZone(d);
    return d.zone == 7;
}

TEST(predictZone_hog_produces_zone_zero) {
        Data d{
        .position = 0
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    // save shots for a single player
    int count = 10;
    float splits[]  = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[]   = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        addShot(d);
    }
    d.split = 5.0;
    predictZone(d);
    return d.zone == 0;
}

TEST(predictZone_through_produces_zone_eleven) {
        Data d{
        .position = 0
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    // save shots for a single player
    int count = 10;
    float splits[]  = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[]   = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        addShot(d);
    }
    d.split = 2.0;
    predictZone(d);
    return d.zone ==11;
}