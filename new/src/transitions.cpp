#include "transitions.hpp"
#include "states.hpp"
#include "event.hpp"
#include "actions.hpp"

#include <iostream>

namespace Stopwatch {

// State entry
void handleEntry(State s, Data& d) {
    switch (s) {
        case IDLE:
            std::cout << "-> Entering IDLE (Resetting UI animations)\n";
            break;
        case RUNNING:
            std::cout << "-> Entering RUNNING (Starting timer)\n";
            break;
        case ZONE_PREDICT:
            std::cout << "-> Entering ZONE_PREDICT (Calculating zone prediction)\n";
            break;
        case SPLIT_PREDICT:
            std::cout << "-> Entering SPLIT_PREDICT (Calculating split prediction)\n";
            break;
        default:
            std::cout << "-> Entering Unknown State\n";
            break;
    }
}

// State exit
void handleExit(State s, Data& d) {
    switch (s) {
        case IDLE:
            std::cout << "<- Exiting IDLE\n";
            break;
        case RUNNING:
            std::cout << "<- Exiting RUNNING (Stopping timer)\n";
            break;
        case ZONE_PREDICT:
            std::cout << "<- Exiting ZONE_PREDICT\n";
            break;
        case SPLIT_PREDICT:
            std::cout << "<- Exiting SPLIT_PREDICT\n";
            break;
        default:
            std::cout << "<- Exiting Unknown State\n";
            break;
    }
}

const Transition transitionTable[] = {
    //  SOURCE_STATE    EVENT           ACTION                  TARGET_STATE
    {   IDLE,           START_STOP,     startTimer,            RUNNING         },
    {   IDLE,           UP,             incrementPosition,     IDLE            },
    {   IDLE,           DOWN,           decrementPosition,     IDLE            },
    {   IDLE,           MODE,           noAction,              SPLIT_PREDICT   },
    {   SPLIT_PREDICT,  MODE,           noAction,              IDLE            },
    {   SPLIT_PREDICT,  START_STOP,     startTimer,            RUNNING         },
    {   SPLIT_PREDICT,  UP,             incrementZone,         SPLIT_PREDICT   },
    {   SPLIT_PREDICT,  DOWN,           decrementZone,         SPLIT_PREDICT   },
    {   RUNNING,        START_STOP,     stopTimer,             ZONE_PREDICT    },
    {   ZONE_PREDICT,   START_STOP,     saveShot,          IDLE            },
    {   ZONE_PREDICT,   UP,             incrementZone,         ZONE_PREDICT    },
    {   ZONE_PREDICT,   DOWN,           decrementZone,         ZONE_PREDICT    },
    {   ZONE_PREDICT,   MODE,           noAction,              IDLE            }
};

const int numTransitions = sizeof(transitionTable) / sizeof(Transition);

}