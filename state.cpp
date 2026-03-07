#include "state.h"
#include "transition.h"
#include "action.h"
#include "entry.h"
#include "draw.h"

state currentState;

// Lookup table
typedef struct {
  void (*entry)();
  int (*transition)(button);
  void (*action)(button);
  int (*draw)();
} StateHandlers;

StateHandlers getHandlersForState(state s) {
  switch(s) {
    case IDLE:
      return { idleEntry, idleTransition, selectPlayer, drawIdle };
    case STOPWATCH_STOPPED:
      return { stopwatchStoppedEntry, stopwatchStoppedTransition, selectZone, drawStopped };
    case STOPWATCH_COUNTING:
      return { stopwatchCountingEntry, stopwatchCountingTransition, defaultAction, drawStopwatchCounting };
    case SPLIT_PREDICT:
      return { splitPredictEntry, splitPredictTransition, predictSplit, drawSplitPredict };
    default:
      return { defaultEntry, defaultTransition, defaultAction, defaultDraw };
  }
}

void setState(state newState) {
  currentState = newState;
}

int doStateTransition(button b) {
  return getHandlersForState(currentState).transition(b);
}

void doStateEntry() {
  getHandlersForState(currentState).entry();
}

void doStateAction(button b) {
  getHandlersForState(currentState).action(b);
}

void doStateDraw() {
  initDraw();
  int doFlush = getHandlersForState(currentState).draw();
  if (doFlush) {
     flushDraw();
  }
}

void doStateAnimate() {
  if (currentState == STOPWATCH_COUNTING ||
      currentState == STOPWATCH_STOPPED || 
      currentState == SPLIT_PREDICT) {
    doStateDraw();
  }
}