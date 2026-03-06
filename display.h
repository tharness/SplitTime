#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 oled;
extern const int OLED_WIDTH;
extern const int OLED_HEIGHT;

void oledSetCursorToCenterText(const String& text, int centerX, int centerY);
void oledSetCursorToCenterText(const char* text, int centerX, int centerY);

void oledSetCursorToCenterTextX(const String& text, int centerX, int y);
void oledSetCursorToCenterTextX(const char* text, int centerX, int y);

void oledSetCursorToRightJustifyText(const String& text, int rightX, int y);
void oledSetCursorToRightJustifyText(const char* text, int rightX, int y);

#endif // DISPLAY_H