#ifndef DATA_H
#define DATA_H

// 8 shots over 8 ends, with potential extra
const int maxShots = 8 * 8 + 8;

namespace Stopwatch {

struct Shot {
    int position;
    float split;
    int zone;
};

struct Data {
    int position = 0;
    int zone;
    unsigned int currentShot = 0;
    float split;
    Shot shots[maxShots];
};

}

#endif // DATA_H