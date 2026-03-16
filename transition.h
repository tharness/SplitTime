#ifndef TRANSITION_H
#define TRANSITION_H

#include "control.h"

int defaultTransition(button);
int idleTransition(button);
int stopwatchStoppedTransition(button);
int recordShotTransition(button);
int stopwatchCountingTransition(button);
int splitPredictTransition(button);
int recordSelectTransition(button);

#endif // TRANSITION_H