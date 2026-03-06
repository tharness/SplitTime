#include "action.h"
#include "data.h"
#include "registers.h"
#include "control.h"

// Helper functions

static int getPlayerIndexByOffset(int offset) {
  int playerCount = sizeof(PLAYERS)/sizeof(PLAYERS[0]);
  // Handle negatives
  return (((currentPlayer + offset) % playerCount) + playerCount) % playerCount;
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