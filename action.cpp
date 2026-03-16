#include "action.h"
#include "data.h"
#include "registers.h"
#include "control.h"
#include "calcs.h"

// Helper functions
static int mod(int a, int b) {
  // Handle negatives
  return ((a % b) + b) % b;
}

// Handler functions
void defaultAction(button) {}

void selectPlayer(button b) {
  switch (b) {
    case UP:
      currentPlayer = mod(currentPlayer + 1, 4);
      break;
    case DOWN:
      currentPlayer = mod(currentPlayer - 1, 4);
      break;
    default:
      break;
  }
}

void selectZone(button b) {
  switch (b) {
    case UP:
      zone = mod(zone + 1, 12);
      zoneFlag = 0;
      break;
    case DOWN:
      zone = mod(zone - 1, 12);
      zoneFlag = 0;
      break;
    default:
      break;
  }
}

void predictSplit(button b) {
  selectZone(b);
  split = getPlayerSplitForZone(currentPlayer, zone);
}

void selectRecordMode(button b) {
  switch (b) {
    case UP:
    case DOWN:
      recordShotData = 1 - recordShotData;
      break;
    default:
      break;
  }
}