#include <LiquidCrystal.h>
#include "display.h"
#include "state.h"
#include "control.h"
#include "data.h"

// KP Keypad constants
const int KP = A0; // PIN
// Floor values for each button
const int KP_NONE = 800;
const int KP_SELECT = 700;
const int KP_LEFT = 450;
const int KP_DOWN = 300;
const int KP_UP = 100;
const int KP_RIGHT = 0;

// LCD
const int LCD_RS = 8;
const int LCD_E = 9;
const int LCD_D4 = 4;
const int LCD_D5 = 5;
const int LCD_D6 = 6;
const int LCD_D7 = 7;
const int LCD_COLS = 16;
const int LCD_ROWS = 2;
LiquidCrystal *lcd = new LiquidCrystal(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

button currentButton = NONE;
unsigned long lastDrawMillis = 0;
const unsigned long DRAW_INTERVAL_MS = 500;

button getButton() {
  const int kp_val = analogRead(KP);
  if (kp_val > KP_NONE) return NONE;
  if (kp_val > KP_SELECT) return SELECT;
  if (kp_val > KP_LEFT) return LEFT;
  if (kp_val > KP_DOWN) return DOWN;
  if (kp_val > KP_UP) return UP;
  if (kp_val > KP_RIGHT) return RIGHT;
}

void setup() {
  // LCD setup
  lcd->createChar(ROCK_CHAR, ROCK_DATA);
  lcd->createChar(ROCK_CHAR_90, ROCK_DATA_90);
  lcd->createChar(ROCK_CHAR_180, ROCK_DATA_180);
  lcd->createChar(ROCK_CHAR_270, ROCK_DATA_270);

  lcd->begin(LCD_COLS, LCD_ROWS);

  setState(IDLE);
  doStateDraw();
}  

void loop() {
  // only handle input if selection has changed to ignore holding
  button previousButton = currentButton;
  currentButton = getButton();
  if (previousButton != currentButton) {
    int stateChanged = doStateTransition(currentButton);
    if (stateChanged) {
      doStateAction(currentButton);
      doStateDraw();
    }
  }
  // Update time while stopwatch is counting
  if (currentState == STOPWATCH_COUNTING) {
    unsigned long now = millis();
    if ((now - lastDrawMillis) >= DRAW_INTERVAL_MS) {
      lastDrawMillis = now;
      doStateDraw();
    }
  }
}
