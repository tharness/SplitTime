#include "_test.h"
#include "actions.h"
#include "data.h"

using namespace Stopwatch;

TEST(one_save_shot_toggle) {
    Data d{
        .saveShots = false
    };
    toggleSaveShots(d);
    return d.saveShots;
}

TEST(two_save_shot_toggle) {
    Data d{
        .saveShots = false
    };
    toggleSaveShots(d);
    toggleSaveShots(d);
    return !d.saveShots;
}