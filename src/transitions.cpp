#include "transitions.h"
#include "states.h"
#include "event.h"
#include "actions.h"

namespace Stopwatch {

// State entry
void handleEntry(State s, Data& d) {
    switch (s) {
        case IDLE:
            enterIdle(d);
            break;
        case RUNNING:
            enterRunning(d);
            break;
        case ZONE_PREDICT:
            enterZonePredict(d);
            break;
        case SPLIT_PREDICT:
            enterSplitPredict(d);
            break;
        default:
            break;
    }
}

// State exit
void handleExit(State s, Data& d) {
    switch (s) {
        case IDLE:
            exitIdle(d);
            break;
        case RUNNING:
            exitRunning(d);
            break;
        case ZONE_PREDICT:
            exitZonePredict(d);
            break;
        case SPLIT_PREDICT:
            exitSplitPredict(d);
            break;
        default:
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