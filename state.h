#ifndef STATE_H
#define STATE_H

#include "control.h"

// State machine
typedef enum state { IDLE, STOPWATCH_COUNTING, STOPWATCH_STOPPED, RECORD_SHOT, SPLIT_PREDICT } state;
extern state currentState;

// Dispatch functions
void setState(state);
int doStateTransition(button);
void doStateEntry();
void doStateAction(button);
void doStateDraw();
void doStateAnimate();

#endif // STATE_H