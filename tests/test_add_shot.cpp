#include "_test.h"
#include "actions.h"
#include "data.h"
#include "linearRegressionModel.h"

using namespace Stopwatch;

TEST(no_add_no_shots) {
    Data d{};
    return d.currentShot == 0;
}

TEST(add_records_shot_data) {
    Data d{
        .position = 2,
        .zone = 9
    };
    LinearRegressionModel model;
    d.predictor_by_position[2].model = &model;
    addShot(d);
    return d.currentShot == 1 && 
        d.shots[0].position == 2 && 
        d.shots[0].zone == 9;
}

TEST(add_records_multiple_shot_data) {
    Data d{
        .position = 2,
        .zone = 9
    };
    LinearRegressionModel model;
    d.predictor_by_position[2].model = &model;
    addShot(d);
    d.position = 3;
    d.zone = 2;
    LinearRegressionModel model2;
    d.predictor_by_position[3].model = &model;
    addShot(d);
    return d.currentShot == 2 && 
        d.shots[0].position == 2 && 
        d.shots[0].zone == 9 &&
        d.shots[1].position == 3 && 
        d.shots[1].zone == 2;
}

TEST(add_too_may_shots_prevents_recording) {
    Data d{
        .currentShot = maxShots
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    addShot(d);
    return d.currentShot == maxShots;
}

TEST(add_single_player_shots_computes_regression) {
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

TEST(add_single_player_shots_ignores_out_of_play) {
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

TEST(add_multiple_player_shots_computes_regression_for_right_player) {
        Data d{
        .position = 0
    };
    LinearRegressionModel model;
    d.predictor_by_position[0].model = &model;
    // save shots for a single player less 2
    int count = 10;
    float splits[]  = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[]   = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count - 2; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        addShot(d);
    }

    // pollute the shots with a different player
    d.position = 1;
    LinearRegressionModel model2;
    d.predictor_by_position[1].model = &model;
    float splits_two[]  = {3.6,     3.7,    3.75};
    float zones_two[]   = {1,       2,      3};
    for (int i = 0; i < 3; i++) {
        d.split = splits_two[i];
        d.zone = zones_two[i];
        addShot(d);
    }

    // save final 2 shots for player 0
    d.position = 0;
    d.split = splits[8];
    d.zone = zones[8];
    addShot(d);
    d.split = splits[9];
    d.zone = zones[9];
    addShot(d);

    // known correct answer
    d.split = 3.75;
    predictZone(d);
    return d.zone == 7;
}