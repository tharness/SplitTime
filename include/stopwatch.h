#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "event.h"
#include "states.h"
#include "data.h"

namespace Stopwatch {

class Stopwatch {
public:
    Stopwatch();
    void handleEvent(Event e);
    void tick(long nowMs);
    State getCurrentState() const;
    const Data& getData() const;
private:
    State currentState;
    Data data;
};

}

#endif // STOPWATCH_H