#include "OLED.h"

void OLED::drawState(Stopwatch::State s, const Stopwatch::Data& d) {
  currentMs = d.nowMs;
  Display::drawState(s, d);
}

void OLED::begin(int fps) {
    frames_per_second = fps;
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    oled.clearDisplay();
    oled.display();
    oled.setTextColor(SSD1306_WHITE);
}

void OLED::clear() {
    oled.clearDisplay();
    frame_counter = 0;
    stateStartMs = currentMs;
}

void OLED::drawPlayer(int pos) {
  const char* PLAYERS[4] = {"Lead", "Second", "Third", "Skip"};
  int refX = OLED_WIDTH / 3;

  if (pos == 0) {
    printText(PLAYERS[pos], 1, 0, 0);
  }
  else if (pos == 1 || pos == 2) {
    int x;
    getTextCenter(PLAYERS[pos], 1, refX*pos, 0, &x, nullptr);
    printText(PLAYERS[pos], 1, x, 0);
  }
  else if (pos == 3) {
    printTextRightJustified(PLAYERS[pos], 1, OLED_WIDTH, 0);
  }
}

void OLED::drawNoSaveIcon(int save, int pos) {
  if (!save)
    if (pos == 0 || pos == 1)
      printTextRightJustified("!", 1, OLED_WIDTH, 0);
    else
      printText("!", 1, 0, 0);
}

void OLED::drawSplit(float split) {
    String s = String(split, 2);
    const char* text = s.c_str();
    int x, y;
    getTextCenter(text, 3, OLED_WIDTH / 2, OLED_HEIGHT / 2, &x, &y);
    printText(text, 3, x, y);
}

void OLED::drawConfidence(float conf, bool right = true) {
    String s = String(conf * 100, 0) + "%";
    const char* text = s.c_str();
    int y;
    getTextCenter(text, 1, 0, OLED_HEIGHT / 2, nullptr, &y);
    if (right)
      printTextRightJustified(text, 1, OLED_WIDTH, y);
    else
     printText(text, 1, 0, y);
}

void OLED::drawZone(int zone) {
    String s;
    if (zone == -1) s = "_";
    else if (zone == 0) s = "HOG";
    else if (zone == 11) s = "THROUGH";
    else s = String(zone);
    const char* text = s.c_str();
    int x;
    getTextCenter(text, 2, OLED_WIDTH / 2, 0, &x, nullptr);
    printTextBottomJustified(text, 2, x, OLED_HEIGHT);
}

void OLED::printText(const char* text, int size, int x, int y) {
  oled.setTextSize(size);
  oled.setCursor(x, y);
  oled.print(text);
}

void OLED::getTextCenter(const char* text, int size, int x, int y, int* outX, int* outY) {
  oled.setTextSize(size);
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  if (outX) *outX = x - w / 2;
  if (outY) *outY = y - h / 2;
}

void OLED::printTextRightJustified(const char* text, int size, int x, int y) {
  oled.setTextSize(size);
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  int textX = x - w;
  oled.setCursor(textX, y);
  oled.print(text);
}

void OLED::printTextBottomJustified(const char* text, int size, int x, int y) {
  oled.setTextSize(size);
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  int textY = y - h;
  oled.setCursor(x, textY);
  oled.print(text);
}

bool OLED::cursorOn() {
    return ((currentMs - stateStartMs) % 2000) < 1000;
}

void OLED::drawStopWatchIcon() {
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

void OLED::drawZoneIcon() {
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

void OLED::draw_IDLE(const Stopwatch::Data d) {
    drawPlayer(d.position);
    drawStopWatchIcon();
    drawNoSaveIcon(d.saveShots, d.position);
    drawSplit(d.split);
    drawConfidence(d.predictor_by_position[d.position].confidence);
    oled.display();
}

void OLED::draw_RUNNING(const Stopwatch::Data d) {
    oled.clearDisplay();
    drawPlayer(d.position);
    drawStopWatchIcon();
    drawNoSaveIcon(d.saveShots, d.position);
    drawSplit(d.split);
    drawConfidence(d.predictor_by_position[d.position].confidence);
    oled.display();
}

void OLED::draw_ZONE_PREDICT(const Stopwatch::Data d) {
    oled.clearDisplay();
    drawPlayer(d.position);
    drawStopWatchIcon();
    drawNoSaveIcon(d.saveShots, d.position);
    drawSplit(d.split);
    drawConfidence(d.predictor_by_position[d.position].confidence);
    drawZone(d.zone);
    if (cursorOn())
      printTextBottomJustified(">", 2, 0, OLED_HEIGHT);
    oled.display();
}

void OLED::draw_SPLIT_PREDICT(const Stopwatch::Data d) {
    oled.clearDisplay();
    drawPlayer(d.position);
    drawZoneIcon();
    drawNoSaveIcon(d.saveShots, d.position);
    drawSplit(d.split);
    drawConfidence(d.predictor_by_position[d.position].confidence, false);
    drawZone(d.zone);
    if (cursorOn())
      printTextBottomJustified(">", 2, 0, OLED_HEIGHT);
    oled.display();
}

void OLED::draw_SAVE_SELECT(const Stopwatch::Data d) {
    oled.clearDisplay();
    drawNoSaveIcon(d.saveShots, d.position);

    int refX = OLED_WIDTH / 2;
    int refY = OLED_HEIGHT / 3;
    int x, y;
    getTextCenter("Erase data?", 1, refX, refY*1, &x, &y);
    printText("Erase data?", 1, x, y);
    if (d.saveShots) {
      getTextCenter("Yes", 2, refX, refY*2, &x, &y);
      printText("Yes", 2, x, y);
    }
    else {
      getTextCenter("No", 2, refX, refY*2, &x, &y);
      printText("No", 2, x, y);
    }
    getTextCenter(">", 2, refX, refY*2, &x, &y);
    if (cursorOn())
      printText(">", 2, 0, y);
    
    oled.display();
}