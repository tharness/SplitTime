#include "_test.h"
#include "actions.h"
#include "data.h"
#include "linearRegressionModel.h"

using namespace Stopwatch;

TEST(rSquared_zero_produces_zero_split) {
        Data d{
        .position = 0,
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    d.predictor_by_position[0].confidence = 0;
    enterSplitPredict(d);
    return d.split == 0;
}

TEST(enterSplitPredict_predicts_split_correctly) {
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
    d.zone = 7;
    enterSplitPredict(d);
    return d.split > 3.761 && d.split < 3.763;
}