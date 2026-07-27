#include "stopwatch.h"
#include "transitions.h"

namespace Stopwatch {

Stopwatch::Stopwatch() : currentState(IDLE) { }

void Stopwatch::handleEvent(Event e) {
    for (int i = 0; i < numTransitions; ++i) {
        const Transition& route = transitionTable[i];
        if (route.source == currentState && route.event == e) {
            handleExit(currentState, data);
            route.action(data);
            currentState = route.target;
            handleEntry(currentState, data);
            return;
        }
    }
}

void tick() {
    
}

State Stopwatch::getCurrentState() const {
    return currentState;
}

const Data& Stopwatch::getData() const {
    return data;
}

}
