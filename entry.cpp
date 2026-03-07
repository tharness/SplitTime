#include "entry.h"
#include "registers.h"
#include "Arduino.h"

void idleEntry() {
  split = 0.0;
}

void defaultEntry() {}

void stopwatchStoppedEntry() {
  zoneCursor = 0;

  unsigned long currentTime = millis();
  split = (currentTime - stopwatchStartTime) / 1000.0;
  // replace with zone prediction logic
  zone = 7;
}

void stopwatchCountingEntry() {
  stopwatchStartTime = millis();
  currentRockRotation = 0;
}

void splitPredictEntry() {
  zoneCursor = 0;

  // default selected zone
  zone = 7;

  // replace with zone prediction logic
  split = zone / 2.0;
}