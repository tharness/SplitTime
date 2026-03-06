#include "draw.h"
#include "display.h"
#include "registers.h"
#include "data.h"
#include "Arduino.h"

static unsigned long lastDrawMillis = 0;
static const unsigned long DRAW_INTERVAL_MS = 500;
static unsigned long stopwatchLastDrawMillis = 0;
static const unsigned long STOPWATCH_DRAW_INTERVAL_MS = 10;

void initDraw() {
  oled.clearDisplay();
}

void flushDraw() {
  oled.display();
}

// Handler Functions

int defaultDraw() { return 0; }

int drawPlayer() {
  int quarterScreen = OLED_WIDTH / 4;
  int eigthScreen = OLED_WIDTH / 8;
  
  oled.setTextSize(1);

  if (currentPlayer == 0) {
    oled.setCursor(0, 0);
  }
  else if (currentPlayer == 1 || currentPlayer == 2) {
    int x = quarterScreen * currentPlayer + eigthScreen;
    oledSetCursorToCenterTextX(PLAYERS[currentPlayer], x, 0);
  }
  else if (currentPlayer == 3) {
    oledSetCursorToRightJustifyText(PLAYERS[currentPlayer], OLED_WIDTH, 0);
  }

  oled.print(PLAYERS[currentPlayer]);

  return 1;
}

int drawIdle() {
  drawPlayer();

  String splitString = String(split, 2);
  oled.setTextSize(2);

  int centerX = OLED_WIDTH / 2;
  int centerY = OLED_HEIGHT / 2;

  oledSetCursorToCenterText(splitString, centerX, centerY);
  oled.print(splitString);

  return 1;
}

int drawStopped() {
  drawPlayer();

  String splitString = String(split, 2);
  oled.setTextSize(2);
  int centerX = OLED_WIDTH / 2;
  int centerY = OLED_HEIGHT / 2;
  oledSetCursorToCenterText(splitString, centerX, centerY);
  oled.print(splitString);

  // print zone prediction
  oledSetCursorToCenterText("_", centerX, centerY + 20);
  if (zonePrediction < 1)
  {
    oled.print("_");
  }
  else if (zoneFlag == 0) {
    // real prediction
    oled.print(zonePrediction);
  } else if (zoneFlag < 0) {
    // lower than recorded data
    oled.print("< ");
    oled.print(zonePrediction);
  } else if (zoneFlag == 1) {
    // greater than recorded data
    oled.print("> ");
    oled.print(zonePrediction);
  }

  return 1;
}

int drawStopwatchCounting() {
  drawPlayer();
  unsigned long now = millis();

  if ((now - stopwatchLastDrawMillis) >= STOPWATCH_DRAW_INTERVAL_MS) {
    stopwatchLastDrawMillis = now;

    String elapsed = String((now - stopwatchStartTime) / 1000.0, 2);
    oled.setTextSize(2);

    int centerX = OLED_WIDTH / 2;
    int centerY = OLED_HEIGHT / 2;

    oledSetCursorToCenterText(elapsed, centerX, centerY);
    oled.print(elapsed);

    return 1;
  }

  return 0;
}