#include "actions.hpp"
#include <iostream>

namespace Stopwatch {

void noAction(Data& d) { }
void incrementPosition(Data& d) { if (++d.position > 3) d.position = 0; }
void decrementPosition(Data& d) { if (--d.position < 0) d.position = 3; }
void startTimer(Data& d)      { }
void stopTimer(Data& d)       {  }
void saveShot(Data& d) {
    if (d.currentShot >= maxShots) return;
    auto& shot = d.shots[d.currentShot++];
    shot.position = d.position;
    shot.split = 3.9; // replace with acual logic later
    shot.zone = d.zone;
}
void incrementZone(Data& d) { if (++d.zone > 11) d.zone = 0; }
void decrementZone(Data& d) { if (--d.zone < 0) d.zone = 11; }

}