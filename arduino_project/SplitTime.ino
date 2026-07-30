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
  const int kp_val = analogRead(KP);
  if (kp_val > KP_NONE) return 0;
  if (kp_val > KP_SELECT) return 1;
  if (kp_val > KP_LEFT) return 2;
  if (kp_val > KP_DOWN) return 3;
  if (kp_val > KP_UP) return 4;
  if (kp_val > KP_RIGHT) return 5;
}

const int FPS = 60;
long lastDrawMs = 0;
bool isTimeToDraw() {
  const long MILLIS_PER_FRAME = 1000 / FPS;
  return millis() - lastDrawMs > MILLIS_PER_FRAME;
}

Stopwatch::Stopwatch s;

void setup() {
  // put your setup code here, to run once:
  initDraw(FPS);
}

void loop() {
  // put your main code here, to run repeatedly:
  s.tick(millis());
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
    clear();
  }
  if (isTimeToDraw()) {
    lastDrawMs = millis();
    drawState(s.getCurrentState(), s.getData());
  }
}