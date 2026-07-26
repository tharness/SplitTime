#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "data.hpp"

namespace Stopwatch {

void noAction(Data& d);
void incrementPosition(Data& d);
void decrementPosition(Data& d);
void startTimer(Data& d);
void stopTimer(Data& d);
void saveShot(Data& d);
void incrementZone(Data& d);
void decrementZone(Data& d);

}

#endif // ACTIONS_HPP