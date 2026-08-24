#include "_test.h"
#include "shotToBytes.h"

using namespace Stopwatch;

TEST(all_zero_shot_all_zero_bytes) {
    Shot s{
        .position = 0,
        .split = 0,
        .zone = 0
    };
    ShotBytes b = shotToBytes(s);
    return b.one == 0b00000000 &&
        b.two == 0;
}

TEST(shot_scenario_one) {
    Shot s{
        .position = 0,
        .split = 3.82,
        .zone = 8
    };
    ShotBytes b = shotToBytes(s);
    return b.one == 0b00010001 &&
        b.two == 0b01111110;
}

TEST(shot_scenario_two) {
    Shot s{
        .position = 1,
        .split = 4.2,
        .zone = 1
    };
    ShotBytes b = shotToBytes(s);
    return b.one == 0b01000011 &&
        b.two == 0b10100100;
}

TEST(shot_scenario_three) {
    Shot s{
        .position = 3,
        .split = 3.23,
        .zone = 11
    };
    ShotBytes b = shotToBytes(s);
    return b.one == 0b11010111 &&
        b.two == 0b01000011;
}

TEST(shot_scenario_four) {
    Shot s{
        .position = 3,
        .split = 4.7,
        .zone = 0
    };
    ShotBytes b = shotToBytes(s);
    return b.one == 0b11000001 &&
        b.two == 0b11010110;
}