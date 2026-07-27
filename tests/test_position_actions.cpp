#include "_test.h"
#include "actions.h"

using namespace Stopwatch;

TEST(increment_position_before_overflow) {
    Data d{
        .position = 0
    };    
    incrementPosition(d);
    return d.position == 1;
}

TEST(increment_position_overflow_wraps) {
    Data d{
        .position = 3
    };    
    incrementPosition(d);
    return d.position == 0;
}

TEST(decrement_position_before_underflow) {
    Data d{
        .position = 2
    };    
    decrementPosition(d);
    return d.position == 1;
}

TEST(decrement_position_underflow_wraps) {
    Data d{
        .position = 0
    };    
    decrementPosition(d);
    return d.position == 3;
}