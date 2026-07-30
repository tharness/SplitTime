#ifndef STATES_H
#define STATES_H

namespace Stopwatch {

enum State {
    IDLE,
    RUNNING,
    ZONE_PREDICT,
    SPLIT_PREDICT,
    SAVE_SELECT
};

}

#endif // STATES_H