#ifndef DATA_HPP
#define DATA_HPP

// 8 shots over 8 eds, with potential extra
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
    Shot shots[maxShots];
};

}

#endif // DATA_HPP