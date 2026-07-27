#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "states.h"
#include "event.h"
#include "data.h"

namespace Stopwatch {

typedef void (&ActionFunc)(Data& r);

struct Transition {
    State source;
    Event event;
    // Performs an action, potentially modifying registers
    ActionFunc action;
    State target;
};

extern const int numTransitions;
extern const Transition transitionTable[];

// Exits given state, potentially modifying registers
void handleExit(State s, Data& r);
// Enters given state, potentially modifying registers
void handleEntry(State s, Data& r);

}

#endif // TRANSITION_H