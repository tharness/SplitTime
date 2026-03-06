#include "entry.h"
#include "registers.h"
#include "Arduino.h"

void idleEntry() {
  split = 0.0;
}

void defaultEntry() {}

void stopwatchStoppedEntry() {
  unsigned long currentTime = millis();
  split = (currentTime - stopwatchStartTime) / 1000.0;
  zonePrediction = 7;
}

void stopwatchCountingEntry() {
  stopwatchStartTime = millis();
  currentRockRotation = 0;
}