#ifndef DISPLAY_H
#define DISPLAY_H

#include "LiquidCrystal.h"

extern LiquidCrystal *lcd;
extern const int LCD_COLS;
extern const int LCD_ROWS;

void clearCharAt(int, int);

#endif // DISPLAY_H