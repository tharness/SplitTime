#include "_test.h"
#include "actions.h"

using namespace Stopwatch;

TEST(increment_zone_before_overflow) {
    Data d{
        .zone = 10
    };    
    incrementZone(d);
    return d.zone == 11;
}

TEST(increment_zone_overflow_wraps) {
    Data d{
        .zone = 11
    };    
    incrementZone(d);
    return d.zone == 0;
}

TEST(decrement_zone_before_underflow) {
    Data d{
        .zone = 5
    };    
    decrementZone(d);
    return d.zone == 4;
}

TEST(decrement_zone_underflow_wraps) {
    Data d{
        .zone = 0
    };    
    decrementZone(d);
    return d.zone == 11;
}