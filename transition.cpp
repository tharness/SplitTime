#include "transition.h"
#include "state.h"

void defaultTransition(button b) {}

void moveRockTransition(button b) {
  if (b == SELECT) currentState = PLAYER_SELECT;
}

void playerSelectTransition(button b) {
  if (b == SELECT) currentState = MOVE_ROCK;
  if (b == LEFT || b == RIGHT) currentState = IDLE;
}

void stopwatchStoppedTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_COUNTING;
  if (b == UP || b == DOWN || b == LEFT || b == RIGHT) currentState = PLAYER_SELECT;
}

void stopwatchCountingTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_STOPPED;
}