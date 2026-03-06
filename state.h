#ifndef STATE_H
#define STATE_H

#include "control.h"

// State machine
typedef enum state { PLAYER_SELECT, IDLE, STOPWATCH_COUNTING, STOPWATCH_STOPPED } state;
extern state currentState;

// Dispatch functions
void setState(state);
int doStateTransition(button);
void doStateEntry();
void doStateAction(button);
void doStateDraw();

#endif // STATE_H