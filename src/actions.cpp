#include "actions.h"
#include <iostream>

namespace Stopwatch {

// transition actions

void noAction(Data& d) { }
void incrementPosition(Data& d) { if (++d.position > 3) d.position = 0; }
void decrementPosition(Data& d) { if (--d.position < 0) d.position = 3; }
void startTimer(Data& d) {}
void stopTimer(Data& d) {}
void saveShot(Data& d) {
    if (d.currentShot >= maxShots) return;
    auto& shot = d.shots[d.currentShot++];
    shot.position = d.position;
    shot.split = d.split;
    shot.zone = d.zone;
}
void incrementZone(Data& d) { if (++d.zone > 11) d.zone = 0; }
void decrementZone(Data& d) { if (--d.zone < 0) d.zone = 11; }

// state entry actions
void enterIdle(Data& d) {}
void enterSplitPredict(Data& d) {}
void enterRunning(Data& d) {}
void enterZonePredict(Data& d) {}

// state exit action
void exitIdle(Data& d) {}
void exitSplitPredict(Data& d) {}
void exitRunning(Data& d) {}
void exitZonePredict(Data& d) {}

}