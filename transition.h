#ifndef TRANSITION_H
#define TRANSITION_H

#include "control.h"

int defaultTransition(button);
int idleTransition(button);
int stopwatchStoppedTransition(button);
int stopwatchCountingTransition(button);

#endif // TRANSITION_H