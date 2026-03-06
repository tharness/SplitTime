#include "action.h"
#include "data.h"
#include "registers.h"
#include "control.h"

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