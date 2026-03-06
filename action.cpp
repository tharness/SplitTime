#include "action.h"
#include "data.h"
#include "registers.h"
#include "control.h"

// Helper functions

static int modPlayerIndex(int index) {
  // Handle negatives
  return (((index) % 4) + 4) % 4;
}

// Handler functions
void defaultAction(button) {}

void selectPlayer(button b) {
  switch (b) {
    case UP:
      currentPlayer = modPlayerIndex(currentPlayer + 1);
      break;
    case DOWN:
      currentPlayer = modPlayerIndex(currentPlayer - 1);
      break;
    default:
      break;
  }
}