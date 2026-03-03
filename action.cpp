#include "action.h"
#include "Arduino.h"
#include "data.h"
#include "registers.h"
#include "control.h"

// Helper functions

static int getPlayerIndexByOffset(int offset) {
  int playerCount = sizeof(PLAYERS)/sizeof(PLAYERS[0]);
  // Handle negatives
  return (((currentPlayer + offset) % playerCount) + playerCount) % playerCount;
}

static int clampRockX(int x) {
  if (x < 0) return 0;
  else if (x > rockXBound) return rockXBound;
  else return x;
}

static int clampRockY(int y) {
  if (y < 0) return 0;
  else if (y > rockYBound) return rockYBound;
  else return y;
}

// Handler functions
void defaultAction(button) {}

void selectPlayer(button b) {
  switch (b) {
    case UP:
      currentPlayer = getPlayerIndexByOffset(1);
      break;
    case DOWN:
      currentPlayer = getPlayerIndexByOffset(-1);
      break;
    default:
      break;
  }
}

void moveRock(button b) {
  oldRockX = rockX;
  oldRockY = rockY;

  switch (b) {
    case RIGHT:
      rockX = clampRockX(rockX + 1);
      break;
    case LEFT:
      rockX = clampRockX(rockX - 1);
      break;
    case UP:
      rockY = clampRockY(rockY - 1);
      break;
    case DOWN:
      rockY = clampRockY(rockY + 1);
      break;
    default:
      break;
  }
}

void idleAction(button) {
  split = 0.0;
}

void stopwatchStoppedAction(button) {
  unsigned long currentTime = millis();
  split = (currentTime - stopwatchStartTime) / 1000.0;
}

void stopwatchCountingAction(button b) {
  stopwatchStartTime = millis();
  currentRockRotation = 0;
}

