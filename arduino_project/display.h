#include "states.h"
#include "data.h"

class Display {
public:
    virtual void begin(int fps);
    virtual void clear() = 0;
    virtual void drawState(Stopwatch::State s, const Stopwatch::Data& d) = 0;
};