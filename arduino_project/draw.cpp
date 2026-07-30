#include "draw.h"

#include <LiquidCrystal.h>

// LCD
const int LCD_RS = 8;
const int LCD_E = 9;
const int LCD_D4 = 4;
const int LCD_D5 = 5;
const int LCD_D6 = 6;
const int LCD_D7 = 7;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void initDraw() {
    lcd.begin(LCD_COLS, LCD_ROWS);
}

void lcdClearCharAt(int col, int row) {
  lcd.setCursor(col, row);
  // Blank Character
  lcd.write(0b00010000);
}

void draw_IDLE(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
}

void draw_RUNNING(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
}

void draw_ZONE_PREDICT(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    lcd.setCursor(6, 1);
    lcd.write(String(d.zone).c_str());
}

void draw_SPLIT_PREDICT(const Stopwatch::Data d) {
    char* positions[] = {"Lead", "Second", "Third", "Skip"};
    lcd.setCursor(0, 0);
    lcd.write(positions[d.position]);
    lcd.setCursor(0, 1);
    lcd.write(String(d.split).c_str());
    lcd.setCursor(6, 1);
    lcd.write(String(d.zone).c_str());
}

void drawState(Stopwatch::State s, const Stopwatch::Data& d) {
    switch (s)
    {
    case Stopwatch::IDLE:
        draw_IDLE(d);
        break;
    case Stopwatch::RUNNING:
        draw_RUNNING(d);
        break;
    case Stopwatch::ZONE_PREDICT:
        draw_ZONE_PREDICT(d);
        break;
    case Stopwatch::SPLIT_PREDICT:
        draw_SPLIT_PREDICT(d);
        break;
    }
}