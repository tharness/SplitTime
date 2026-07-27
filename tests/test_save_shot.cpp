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