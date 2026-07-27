#include "transitions.h"
#include "states.h"
#include "event.h"
#include "actions.h"

#include <iostream>

namespace Stopwatch {

// State entry
void handleEntry(State s, Data& d) {
    switch (s) {
        case IDLE:
            std::cout << "-> Entering IDLE\n";
            enterIdle(d);
            break;
        case RUNNING:
            std::cout << "-> Entering RUNNING\n";
            enterRunning(d);
            break;
        case ZONE_PREDICT:
            std::cout << "-> Entering ZONE_PREDICT\n";
            enterZonePredict(d);
            break;
        case SPLIT_PREDICT:
            std::cout << "-> Entering SPLIT_PREDICT\n";
            enterSplitPredict(d);
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
            exitIdle(d);
            break;
        case RUNNING:
            std::cout << "<- Exiting RUNNING\n";
            exitRunning(d);
            break;
        case ZONE_PREDICT:
            std::cout << "<- Exiting ZONE_PREDICT\n";
            exitZonePredict(d);
            break;
        case SPLIT_PREDICT:
            std::cout << "<- Exiting SPLIT_PREDICT\n";
            exitSplitPredict(d);
            break;
        default:
            std::cout << "<- Exiting Unknown State\n";
            break;
    }
}

const Transition transitionTable[] = {
    //  SOURCE_STATE    EVENT           ACTION                 TARGET_STATE
    {   IDLE,           START_STOP,     startTimer,            RUNNING         },
    {   IDLE,           UP,             incrementPosition,     IDLE            },
    {   IDLE,           DOWN,           decrementPosition,     IDLE            },
    {   IDLE,           MODE,           setZoneToSeven,        SPLIT_PREDICT   },
    {   SPLIT_PREDICT,  MODE,           noAction,              IDLE            },
    {   SPLIT_PREDICT,  START_STOP,     startTimer,            RUNNING         },
    {   SPLIT_PREDICT,  UP,             incrementZone,         SPLIT_PREDICT   },
    {   SPLIT_PREDICT,  DOWN,           decrementZone,         SPLIT_PREDICT   },
    {   RUNNING,        START_STOP,     predictZone,           ZONE_PREDICT    },
    {   ZONE_PREDICT,   START_STOP,     saveShot,              IDLE            },
    {   ZONE_PREDICT,   UP,             incrementZone,         ZONE_PREDICT    },
    {   ZONE_PREDICT,   DOWN,           decrementZone,         ZONE_PREDICT    },
    {   ZONE_PREDICT,   MODE,           noAction,              IDLE            }
};

const int numTransitions = sizeof(transitionTable) / sizeof(Transition);

}