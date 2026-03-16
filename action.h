#ifndef ACTION_H
#define ACTION_H

#include "control.h"

// Action handlers (called when pressing button in current state)
void defaultAction(button);
void selectPlayer(button);
void selectZone(button);
void predictSplit(button);
void selectRecordMode(button);

#endif // ACTION_H