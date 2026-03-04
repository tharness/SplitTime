#include "transition.h"
#include "state.h"

int defaultTransition(button b) { 
  return 0;
}

int moveRockTransition(button b) {
  if (b == SELECT) currentState = PLAYER_SELECT;
  else return 0;
  
  return 1;
}

int playerSelectTransition(button b) {
  if (b == SELECT) currentState = MOVE_ROCK;
  else if (b == LEFT || b == RIGHT) currentState = IDLE;
  else return 0;

  return 1;
}

int stopwatchStoppedTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_COUNTING;
  else if (b == UP || b == DOWN || b == LEFT || b == RIGHT) currentState = PLAYER_SELECT;
  else return 0;

  return 1;
}

int stopwatchCountingTransition(button b) {
  if (b == SELECT) currentState = STOPWATCH_STOPPED;
  else return 0;

  return 1;
}