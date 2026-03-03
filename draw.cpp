#include "draw.h"
#include "display.h"
#include "registers.h"
#include "data.h"
#include "Arduino.h"

// Handler Functions

void defaultDraw() {}

void writePlayer() {
  // Clear 6 chars (max player name length) on bottom of screen
  for (int i = 0; i < 6; i++) {
    clearCharAt(i, 1);
  }
  lcd->setCursor(0, 1);
  lcd->print(PLAYERS[currentPlayer]);
}

void drawRock() {
  clearCharAt(oldRockX, oldRockY);
  lcd->setCursor(rockX, rockY);
  lcd->write(ROCK_CHAR);
}

void drawStopped() {
  // Clear old split time
  for (int i = 0; i < 4; i++) {
    clearCharAt(i, 0);
  }
  lcd->setCursor(0, 0);
  lcd->print(split, 2);
}

void drawStopwatchCounting() {
  // Clear old time
  for (int i = 0; i < 4; i++) {
    clearCharAt(i, 0);
  }
  lcd->setCursor(2, 0);
  lcd->write(ROCK_ROTATIONS[currentRockRotation]);
  currentRockRotation = (currentRockRotation + 1) % sizeof(ROCK_ROTATIONS)/sizeof(ROCK_ROTATIONS[0]);
}