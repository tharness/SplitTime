#include "transition.h"
#include "state.h"

int defaultTransition(button b) { 
  return 0;
}

int idleTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_COUNTING;
  else return 0;

  return 1;
}

int stopwatchStoppedTransition(button b) {
  if (b == SELECT) currentState = IDLE;
  else return 0;

  return 1;
}

int stopwatchCountingTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_STOPPED;
  else return 0;

  return 1;
}