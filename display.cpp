#include "display.h"

void clearCharAt(int col, int row) {
  lcd->setCursor(col, row);
  // Blank Character
  lcd->write(0b00010000);
}