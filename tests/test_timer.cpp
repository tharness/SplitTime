#include "_test.h"
#include "actions.h"
#include "data.h"
#include "stopwatch.h"

using namespace Stopwatch;

TEST(tick_not_RUNNING_updates_now_not_split) {
    Stopwatch::Stopwatch s;
    if (s.getCurrentState() == RUNNING) return false;
    auto& data = s.getData();
    if (data.split != 0) return false;
    s.tick(1000);
    return data.nowMs == 1000
        && data.split == 0;
}

TEST(tick_RUNNING_updates_now_and_split) {
    Stopwatch::Stopwatch s;
    if (s.getCurrentState() != SAVE_SELECT) return false;
    s.handleEvent(START_STOP);
    if (s.getCurrentState() != IDLE) return false;
    s.handleEvent(START_STOP);
    if (s.getCurrentState() != RUNNING) return false;
    auto& data = s.getData();
    if (data.split != 0) return false;
    s.tick(1000);
    return data.nowMs == 1000
        && data.split == 1.0;
}

TEST(start_time_sets_startMs) {
    Stopwatch::Stopwatch s;
    if (s.getCurrentState() != SAVE_SELECT) return false;
    s.handleEvent(START_STOP);
    if (s.getCurrentState() != IDLE) return false;
    s.tick(1000);
    s.handleEvent(START_STOP);
    if (s.getCurrentState() != RUNNING) return false;
    auto& data = s.getData();
    if (data.split != 0) return false;
    s.tick(2000);
    return data.startMs == 1000
        && data.split == 1.0;
}