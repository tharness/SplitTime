#include "_test.h"
#include "actions.h"
#include "data.h"
#include "stopwatch.h"

using namespace Stopwatch;

TEST(integration_test_shots_generate_correct_model) {
    Stopwatch::Stopwatch s;

    // exit save select screen
    s.handleEvent(START_STOP);

    // simulate split -> zone combos 3.0 -> 9 and 4.0 -> 1
    // slope of -8 and intercept of 33

    s.handleEvent(START_STOP);
    s.tick(3000);
    s.handleEvent(START_STOP);
    // zone should indicate -1 due to insufficient data
    for (int i = 0; i <= 9; ++i) {
        s.handleEvent(UP);
    }
    // save shot
    s.handleEvent(START_STOP);

    s.handleEvent(START_STOP);
    s.tick(7000);
    s.handleEvent(START_STOP);
    // zone should indicate -1 due to insufficient data
    for (int i = 0; i <= 1; ++i) {
        s.handleEvent(UP);
    }
    // save shot
    s.handleEvent(START_STOP);

    // save bad data
    s.handleEvent(START_STOP);
    s.tick(15000);
    s.handleEvent(START_STOP);
    // discard shot
    s.handleEvent(MODE);

    // now test split 3.5, should generate zone of 5
    s.handleEvent(START_STOP);
    s.tick(18500);
    s.handleEvent(START_STOP);
    
    return s.getData().zone == 5;
}