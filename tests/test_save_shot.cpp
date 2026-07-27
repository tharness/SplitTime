#include "_test.h"
#include "actions.h"
#include "data.h"

using namespace Stopwatch;

TEST(no_save_no_shots) {
    Data d{};
    return d.currentShot == 0;
}

TEST(save_records_shot_data) {
    Data d{
        .position = 2,
        .zone = 9
    };
    saveShot(d);
    return d.currentShot == 1 && 
        d.shots[0].position == 2 && 
        d.shots[0].zone == 9;
}

TEST(save_records_multiple_shot_data) {
    Data d{
        .position = 2,
        .zone = 9
    };
    saveShot(d);
    d.position = 3;
    d.zone = 2;
    saveShot(d);
    return d.currentShot == 2 && 
        d.shots[0].position == 2 && 
        d.shots[0].zone == 9 &&
        d.shots[1].position == 3 && 
        d.shots[1].zone == 2;
}

TEST(save_too_may_shots_prevets_save) {
    Data d{
        .currentShot = maxShots
    };
    saveShot(d);
    return d.currentShot == maxShots;
}

TEST(save_single_player_shots_computes_regression) {
    Data d{
        .position = 0
    };
    // save shots for a single player
    int count = 10;
    float splits[] = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[] = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        saveShot(d);
    }

    // known correct values
    auto& model = d.models_by_position[0];
    return model.rSquared > 0 
    && model.slope > -14.9 && model.slope < -14.7
    && model.intercept > 62.68 && model.intercept < 62.70
    && model.rSquared > 0.9425 && model.rSquared < 0.9427;
}

TEST(save_multiple_player_shots_computes_regression_for_right_player) {
        Data d{
        .position = 0
    };
    // save shots for a single player less 2
    int count = 10;
    float splits[]  = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float zones[]   = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    for (int i = 0; i < count - 2; i++) {
        d.split = splits[i];
        d.zone = zones[i];
        saveShot(d);
    }

    // pollute the shots with a different player
    d.position = 1;
    float splits_two[]  = {3.6,     3.7,    3.75};
    float zones_two[]   = {1,       2,      3};
    for (int i = 0; i < 3; i++) {
        d.split = splits_two[i];
        d.zone = zones_two[i];
        saveShot(d);
    }

    // save final 2 shots for player 0
    d.position = 0;
    d.split = splits[8];
    d.zone = zones[8];
    saveShot(d);
    d.split = splits[9];
    d.zone = zones[9];
    saveShot(d);

    // known correct values
    auto& model = d.models_by_position[0];
    return model.rSquared > 0 
    && model.slope > -14.9 && model.slope < -14.7
    && model.intercept > 62.68 && model.intercept < 62.70
    && model.rSquared > 0.9425 && model.rSquared < 0.9427;
}