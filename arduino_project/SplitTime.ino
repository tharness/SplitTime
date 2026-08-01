#include "stopwatch.h"
#include "draw.h"

// KP Keypad constants
const int KP = A0; // PIN
// Floor values for each button
const int KP_NONE = 800;
const int KP_SELECT = 700;
const int KP_LEFT = 450;
const int KP_DOWN = 300;
const int KP_UP = 100;
const int KP_RIGHT = 0;

int currentButton = 0;

int getButton() {
  const int DEBOUNCE_MS = 5;
  static long lastDebounceTime = 0;
  static int previousValue = 0;
  int currentValue = 0;

  const int kp_val = analogRead(KP);
  if (kp_val > KP_NONE) currentValue = 0;
  else if (kp_val > KP_SELECT) currentValue = 1;
  else if (kp_val > KP_LEFT) currentValue = 2;
  else if (kp_val > KP_DOWN) currentValue = 3;
  else if (kp_val > KP_UP) currentValue = 4;
  else if (kp_val > KP_RIGHT) currentValue = 5;

  if (currentValue != previousValue) lastDebounceTime = millis();
  previousValue = currentValue;
  if (millis() - lastDebounceTime > DEBOUNCE_MS) return currentValue;
}

// draw timing
const int FPS = 60;
long lastDrawMs = 0;
bool isTimeToDraw() {
  const long MILLIS_PER_FRAME = 1000 / FPS;
  return millis() - lastDrawMs > MILLIS_PER_FRAME;
}

// save logic
int nextShotToSave = 0;
void saveShot(int shotNumber, Stopwatch::Shot shot) {

}

Stopwatch::Stopwatch s;

void setup() {
  initDraw(FPS);
}

void loop() {
  // feed the clock
  s.tick(millis());
  // detect input
  int previousButton = currentButton;
  currentButton = getButton();
  if (previousButton != currentButton && currentButton != 0 && currentButton != 5) {
    Stopwatch::Event e;
    switch (currentButton) {
      case 1:
        e = Stopwatch::START_STOP;
        break;
      case 2:
        e = Stopwatch::MODE;
        break;
      case 3:
        e = Stopwatch::DOWN;
        break;
      case 4:
        e = Stopwatch::UP;
        break;
    }
    s.handleEvent(e);
    // save shot if required
    if (s.getData().saveShots && s.getData().currentShot - 1 == nextShotToSave) {
      saveShot(nextShotToSave, s.getData().shots[nextShotToSave]);
      ++nextShotToSave;
    }
    // refresh screen
    clear();
  }
  // draw timing
  if (isTimeToDraw()) {
    lastDrawMs = millis();
    drawState(s.getCurrentState(), s.getData());
  }
}