#include "entry.h"
#include "registers.h"
#include "Arduino.h"
#include "calcs.h"

void idleEntry() {
  split = 0.0;
}

void defaultEntry() {}

void stopwatchStoppedEntry() {
  zoneCursor = 0;

  unsigned long currentTime = millis();
  split = (currentTime - stopwatchStartTime) / 1000.0;
  zoneFlag = getPlayerSplitStatus(currentPlayer, split);
  zone = getZoneforPlayerSplit(currentPlayer, split);
}

void stopwatchCountingEntry() {
  stopwatchStartTime = millis();
}

void recordShotEntry() {
  addShotForPlayer(currentPlayer, split, zone);
}

void splitPredictEntry() {
  zoneCursor = 0;

  // default selected zone
  zone = 7;
  zoneFlag = 0;
  
  split = getPlayerSplitForZone(currentPlayer, zone);
}