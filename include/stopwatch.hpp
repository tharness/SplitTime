#ifndef STOPWATCH_HPP
#define STOPWATCH_HPP

#include "event.hpp"
#include "states.hpp"
#include "data.hpp"

namespace Stopwatch {

class Stopwatch {
public:
    Stopwatch();
    void handleEvent(Event e);
    void tick();
    State getCurrentState() const;
    const Data& getData() const;
private:
    State currentState;
    Data data;
};

}

#endif // STOPWATCH_HPP