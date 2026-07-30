#include "actions.h"
#include "calculations.h"

namespace Stopwatch {

// transition actions

void noAction(Data& d) {}
void incrementPosition(Data& d) { if (++d.position > 3) d.position = 0; }
void decrementPosition(Data& d) { if (--d.position < 0) d.position = 3; }
void startTimer(Data& d) { d.startMs = d.nowMs; }
void predictZone(Data& d) {
    auto& model = d.models_by_position[d.position];
    // if there is some amount of model fit, interpolated and round
    if (model.rSquared > 0) {
        d.zone = (int)((model.slope * d.split + model.intercept) + 0.5);
        //if hog or through, clamp to 0 and 11 respetively
        if (d.zone < 1) d.zone = 0;
        else if (d.zone > 10) d.zone = 11;
    }
    else d.zone = -1;
}
void saveShot(Data& d) {
    // discard if maximum shot count reached
    if (d.currentShot >= maxShots) return;
    // save shot
    auto& shot = d.shots[d.currentShot++];
    shot.position = d.position;
    shot.split = d.split;
    shot.zone = d.zone;

    // do regression

    // max shots per player in 3-person game is 3 * 8 + 3 = 27
    const int MAX_COUNT = 27;
    float splits[MAX_COUNT];
    float zones[MAX_COUNT];
    int count = 0;
    // go through d.shots, filter by player, adding to buffers and keeping count
    // do not include in the regression shots that were out of play
    for (int i = 0; i < d.currentShot; ++i) {
        auto& shot = d.shots[i];
        if (shot.position == d.position 
            && count < MAX_COUNT
            && shot.zone >= 1 && shot.zone <= 10)
        {
            splits[count] = shot.split;
            zones[count] = shot.zone;
            ++count;
        }
    }

    auto& model = d.models_by_position[d.position];
    linearRegressionLeastSquares(splits, zones, count, model.slope, model.intercept, model.rSquared);
}
void incrementZone(Data& d) { if (++d.zone > 11) d.zone = 0; }
void decrementZone(Data& d) { if (--d.zone < 0) d.zone = 11; }
void setZoneToSeven(Data& d) { d.zone = 7; }

// state entry actions
void enterIdle(Data& d) { d.split = 0; }
void enterSplitPredict(Data& d) {
    auto& model = d.models_by_position[d.position];
    if (model.rSquared > 0) d.split = ((float)d.zone - model.intercept) / model.slope;
    else d.split = 0;
}
void enterRunning(Data& d) {}
void enterZonePredict(Data& d) {}

// state exit action
void exitIdle(Data& d) {}
void exitSplitPredict(Data& d) {}
void exitRunning(Data& d) {}
void exitZonePredict(Data& d) {}

}