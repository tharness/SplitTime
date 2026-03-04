#include "state.h"
#include "transition.h"
#include "action.h"
#include "draw.h"

state currentState;

// Lookup table
typedef struct {
  int (*transition)(button);
  void (*action)(button);
  void (*draw)();
} StateHandlers;

StateHandlers getHandlersForState(state s) {
  switch(s) {
    case MOVE_ROCK: 
      return { moveRockTransition, moveRock, drawRock };
    case PLAYER_SELECT: 
      return { playerSelectTransition, selectPlayer, writePlayer };
    case IDLE:
      return { stopwatchStoppedTransition, idleAction, drawStopped };
    case STOPWATCH_STOPPED:
      return { stopwatchStoppedTransition, stopwatchStoppedAction, drawStopped };
    case STOPWATCH_COUNTING:
      return { stopwatchCountingTransition, stopwatchCountingAction, drawStopwatchCounting };
    default:
      return { defaultTransition, defaultAction, defaultDraw };
  }
}

void setState(state newState) {
  currentState = newState;
}

int doStateTransition(button b) {
  return getHandlersForState(currentState).transition(b);
}

void doStateAction(button b) {
  getHandlersForState(currentState).action(b);
}

void doStateDraw() {
  getHandlersForState(currentState).draw();
}