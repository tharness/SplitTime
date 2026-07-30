#ifndef ACTIONS_H
#define ACTIONS_H

#include "data.h"

namespace Stopwatch {

// transition actions

void noAction(Data& d);
void incrementPosition(Data& d);
void decrementPosition(Data& d);
void startTimer(Data& d);
void predictZone(Data& d);
void addShot(Data& d);
void incrementZone(Data& d);
void decrementZone(Data& d);
void setZoneToSeven(Data& d);
void toggleSaveShots(Data& d);

// state entry actions
void enterIdle(Data& d);
void enterSplitPredict(Data& d);
void enterRunning(Data& d);
void enterZonePredict(Data& d);

// state exit action
void exitIdle(Data& d);
void exitSplitPredict(Data& d);
void exitRunning(Data& d);
void exitZonePredict(Data& d);

}

#endif // ACTIONS_H