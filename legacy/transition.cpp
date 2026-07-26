#include "transition.h"
#include "state.h"

int defaultTransition(button b) { 
  return 0;
}

int idleTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_COUNTING;
  else if (b == CANCEL) currentState = SPLIT_PREDICT;
  else return 0;

  return 1;
}

int stopwatchStoppedTransition(button b) {
  if (b == SELECT) currentState = RECORD_SHOT;
  else if (b == CANCEL) currentState = IDLE;
  else return 0;

  return 1;
}

int recordShotTransition(button b) {
  currentState = IDLE;

  return 1;
}

int stopwatchCountingTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_STOPPED;
  else if (b == CANCEL) currentState = STOPWATCH_STOPPED;
  else return 0;

  return 1;
}

int splitPredictTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_COUNTING;
  else if (b == CANCEL) currentState = IDLE;
  else return 0;

  return 1;
}

int recordSelectTransition(button b) {
  if (b == SELECT) currentState = IDLE;
  else return 0;

  return 1;
}