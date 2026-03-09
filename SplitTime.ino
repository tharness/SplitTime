#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display.h"
#include "state.h"
#include "control.h"
#include "data.h"

// Button pin constants
const int B_SELECT = 2;
const int B_UP = 3;
const int B_DOWN = 4;
const int B_CANCEL = 5;

// OLED display
const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 64;
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT);

button currentButton = NONE;

button getButton() {
  if (digitalRead(B_SELECT) == LOW) return SELECT;
  if (digitalRead(B_UP) == LOW) return UP;
  if (digitalRead(B_DOWN) == LOW) return DOWN;
  if (digitalRead(B_CANCEL) == LOW) return CANCEL;
  return NONE;
}

void setup() {
  // OLED setup
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.clearDisplay();
  oled.display();
  oled.setTextColor(SSD1306_WHITE);

  // Input setup
  pinMode(B_SELECT, INPUT_PULLUP);
  pinMode(B_UP, INPUT_PULLUP);
  pinMode(B_DOWN, INPUT_PULLUP);
  pinMode(B_CANCEL, INPUT_PULLUP);

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
      doStateEntry();
    } else {
      doStateAction(currentButton);
    }
    doStateDraw();
  }
  doStateAnimate();
}
