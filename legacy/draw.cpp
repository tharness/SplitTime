#include "draw.h"
#include "display.h"
#include "registers.h"
#include "data.h"
#include "Arduino.h"

static unsigned long cursorLastDrawMillis = 0;
static const unsigned long CURSOR_DRAW_INTERVAL_MS = 500;
static unsigned long stopwatchLastDrawMillis = 0;
static const unsigned long STOPWATCH_DRAW_INTERVAL_MS = 10;
static int lastDrawnZone = -1;
static int lastRecordSelect = 0;

void initDraw() {
  oled.clearDisplay();
}

void flushDraw() {
  oled.display();
}

// Handler Functions

int defaultDraw() { return 0; }

void drawPlayer() {
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
}

void drawStopWatchIcon() {
  int radius = 6;
  int x = radius;
  int y = OLED_HEIGHT/2;

  // outline
  oled.drawCircle(x, y, radius, SSD1306_WHITE);
  // left button
  oled.drawLine(0, y - radius, 2, y - radius + 2, SSD1306_WHITE);
  // top button
  oled.drawLine(x, y - radius - 2, x, y - radius, SSD1306_WHITE);
  // needle
  oled.drawLine(x, y, x + radius - 4, y - radius + 2, SSD1306_WHITE);
}

void drawZoneIcon() {
  int iceWidth = 17;
  int iceLeft = OLED_WIDTH - iceWidth;
  int iceRight = OLED_WIDTH - 1;
  int iceBottom = OLED_HEIGHT - 10 - 1;
  int radius = iceWidth / 2;
  int houseCenterY = iceBottom;
  int houseCenterX = iceLeft + radius;

  // ice outline
  oled.drawRect(iceLeft, 10, iceWidth, iceBottom, SSD1306_WHITE);
  // erace top line of ice
  oled.drawLine(iceLeft, 10, iceRight, 10, SSD1306_BLACK);
  // hog line
  oled.drawLine(iceLeft, 20, iceRight, 20, SSD1306_WHITE);

  //house
  oled.drawCircle(houseCenterX, houseCenterY, radius, SSD1306_WHITE);
  oled.fillCircle(houseCenterX, houseCenterY, radius / 2, SSD1306_WHITE);
  oled.fillCircle(houseCenterX, houseCenterY, radius / 4, SSD1306_BLACK);
  oled.fillCircle(houseCenterX, houseCenterY, radius / 8, SSD1306_WHITE);
}

int drawIdle() {
  drawPlayer();
  drawStopWatchIcon();

  String splitString = String(split, 2);
  oled.setTextSize(3);

  int centerX = OLED_WIDTH / 2;
  int centerY = OLED_HEIGHT / 2;

  oledSetCursorToCenterText(splitString, centerX, centerY);
  oled.print(splitString);

  return 1;
}

int drawZoneSelect() {
  int redraw = lastDrawnZone != zone;
  if (redraw) {
    lastDrawnZone = zone;
  }

  // print split time
  String splitString = String(split, 2);
  oled.setTextSize(3);
  int centerX = OLED_WIDTH / 2;
  int centerY = OLED_HEIGHT / 2;
  oledSetCursorToCenterText(splitString, centerX, centerY);
  oled.print(splitString);

  // print zone prediction
  String zoneText;
  // no data
  if (zone < 0) {
    zoneText = " ";
  }
  // real prediction/input
  else {
    // zone 0 and 11 come from user input
    if (zone == 0) {
      zoneText = "HOG";
    } else if (zone == 11) {
      zoneText = "THROUGH";
    } else {
      zoneText = String(zone);
    }
  }
  // lower than any recorded zone
  if (zoneFlag < 0) {
    zoneText = "< " + zoneText;
  } 
  // greater than any recorded zone
  else if (zoneFlag == 1) {
    zoneText = "> " + zoneText;
  }

  oled.setTextSize(2);
  oledSetCursorToCenterText(zoneText, centerX, 0);
  int x = oled.getCursorX();
  // leave room for cursor below
  oledSetCursorToBottomJustifyText(zoneText, x, OLED_HEIGHT - 2);
  int y = oled.getCursorY();
  oled.print(zoneText);
  
  // animated cursor for zone selection
  unsigned long now = millis();
  if ((now - cursorLastDrawMillis) >= CURSOR_DRAW_INTERVAL_MS) {
    cursorLastDrawMillis = now;
    if (zoneCursor) {
      int w;
      oled.getTextBounds(zoneText, 0, 0, NULL, NULL, &w, NULL);
      int x = OLED_WIDTH / 2 - w / 2;
      oled.writeFastHLine(x, OLED_HEIGHT - 1, w, 1);
    }
    zoneCursor = !zoneCursor;
    redraw = 1;
  }

  return redraw;
}

int drawStopped() {
  drawPlayer();
  drawStopWatchIcon();
  return drawZoneSelect();
}

int drawSplitPredict() {
  drawPlayer();
  drawZoneIcon();
  return drawZoneSelect();
}

int drawStopwatchCounting() {
  unsigned long now = millis();

  if ((now - stopwatchLastDrawMillis) >= STOPWATCH_DRAW_INTERVAL_MS) {
    drawPlayer();
    drawStopWatchIcon();

    stopwatchLastDrawMillis = now;

    String elapsed = String((now - stopwatchStartTime) / 1000.0, 2);
    oled.setTextSize(3);

    int centerX = OLED_WIDTH / 2;
    int centerY = OLED_HEIGHT / 2;

    oledSetCursorToCenterText(elapsed, centerX, centerY);
    oled.print(elapsed);

    return 1;
  }

  return 0;
}

int drawRecordSelect() {
  if (lastRecordSelect == recordShotData) {
    lastRecordSelect = 1 - recordShotData;
    return 0;
  }

  char* title = "Record shot data?";
  oled.setTextSize(1);
  int centerX = OLED_WIDTH / 2;

  oledSetCursorToCenterText(title, centerX, 0);
  int x = oled.getCursorX();
  oled.setCursor(x, 0);
  oled.print(title);

  oled.setTextSize(2);
  int centerY = OLED_HEIGHT / 2;
  if (recordShotData) {
    char* selection = "Yes";
    oledSetCursorToCenterText(selection, 0, centerY);
    int y = oled.getCursorY();
    oled.setCursor(0, y);
    oled.print(selection);
  }
  else {
    char* selection = "No";
    oledSetCursorToCenterText(selection, 0, centerY);
    int y = oled.getCursorY();
    oledSetCursorToRightJustifyText(selection, OLED_WIDTH - 1, y);
    oled.print(selection);
  }

  return 1;
}