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