#ifndef DATA_H
#define DATA_H

// 8 shots over 8 ends, with potential extra
const int maxShots = 8 * 8 + 8;

namespace Stopwatch {

struct Shot {
    int position = 0;
    float split = 0;
    int zone = 0;
};

struct Model {
    float slope = 0;
    float intercept = 0;
    float rSquared = 0;
};

struct Data {
    int position = 0;
    int zone;
    unsigned int currentShot = 0;
    float split = 0;
    Shot shots[maxShots];
    Model models_by_position[4];
    long nowMs = 0;
    long startMs = 0;
    bool saveShots = false;
};

}

#endif // DATA_H