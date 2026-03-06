#include "display.h"

void lcdClearCharAt(int col, int row) {
  lcd->setCursor(col, row);
  // Blank Character
  lcd->write(0b00010000);
}

void oledSetCursorToCenterText(const String& text, int centerX, int centerY) {
  oledSetCursorToCenterText(text.c_str(), centerX, centerY);
}

void oledSetCursorToCenterText(const char* text, int centerX, int centerY) {
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  int textCenterX = centerX - w / 2;
  int textCenterY = centerY - h / 2;  
  oled.setCursor(textCenterX, textCenterY);
}