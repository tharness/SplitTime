#include "display.h"

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

void oledSetCursorToCenterTextX(const String& text, int centerX, int y) {
  oledSetCursorToCenterTextX(text.c_str(), centerX, y);
}

void oledSetCursorToCenterTextX(const char* text, int centerX, int y) {
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  int textCenterX = centerX - w / 2;
  oled.setCursor(textCenterX, y);
}

void oledSetCursorToRightJustifyText(const String& text, int rightX, int y) {
  oledSetCursorToRightJustifyText(text.c_str(), rightX, y);
}

void oledSetCursorToRightJustifyText(const char* text, int rightX, int y) {
  int w, h;
  oled.getTextBounds(text, 0, 0, NULL, NULL, &w, &h);
  int textX = rightX - w;
  oled.setCursor(textX, y);
}