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
            enterIdle(d);
            std::cout << "-> Entering IDLE\n";
            std::cout << d.split << std::endl;
            std::cout << d.position << std::endl;
            break;
        case RUNNING:
            enterRunning(d);
            std::cout << "-> Entering RUNNING\n";
            std::cout << d.position << std::endl;
            break;
        case ZONE_PREDICT:
            enterZonePredict(d);
            std::cout << "-> Entering ZONE_PREDICT\n";
            std::cout << d.split << std::endl;
            std::cout << d.zone << std::endl;
            std::cout << d.position << std::endl;
            break;
        case SPLIT_PREDICT:
            enterSplitPredict(d);
            std::cout << "-> Entering SPLIT_PREDICT\n";
            std::cout << d.split << std::endl;
            std::cout << d.zone << std::endl;
            std::cout << d.position << std::endl;
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
            exitIdle(d);
            std::cout << "<- Exiting IDLE\n";
            break;
        case RUNNING:
            exitRunning(d);
            std::cout << "<- Exiting RUNNING\n";
            break;
        case ZONE_PREDICT:
            exitZonePredict(d);
            std::cout << "<- Exiting ZONE_PREDICT\n";
            break;
        case SPLIT_PREDICT:
            exitSplitPredict(d);
            std::cout << "<- Exiting SPLIT_PREDICT\n";
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