#include "actions.h"
#include "calculations.h"
#include <cmath>

namespace Stopwatch {

// transition actions

void noAction(Data& d) { }
void incrementPosition(Data& d) { if (++d.position > 3) d.position = 0; }
void decrementPosition(Data& d) { if (--d.position < 0) d.position = 3; }
void startTimer(Data& d) {}
void stopTimer(Data& d) {
    auto& model = d.models_by_position[d.position];
    if (model.rSquared > 0) d.zone = round(model.slope * d.split + model.intercept);
    else d.zone = -1;
}
void saveShot(Data& d) {
    if (d.currentShot >= maxShots) return;
    auto& shot = d.shots[d.currentShot++];
    shot.position = d.position;
    shot.split = d.split;
    shot.zone = d.zone;
    // do regression
    // REPLACE WITH REAL PLAYER SHOT DATA
    float x[] = {3.5,   3.6,    3.65,   3.7,    3.8,    3.85,   3.9,    4,  4.1,    4.2};
    float y[] = {10,    9,      10,     9,      7,      5,      4,      3,  2,      1};
    auto& model = d.models_by_position[d.position];
    linearRegressionLeastSquares(x, y, sizeof(x)/sizeof(float), model.slope, model.intercept, model.rSquared);
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