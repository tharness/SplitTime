#include <EEPROM.h>
#include "stopwatch.h"
#include "draw.h"
#include "shotToBytes.h"

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

// EEPROM
bool initialEraseComplete = false;
void eraseEEPROM() {
  for (int i = 0 ; i < EEPROM.length() ; ++i) {
    EEPROM.update(i, 0);
  }
}

// save logic
void saveShot(int shotNumber, Stopwatch::Shot shot) {
  // convert to encoded bytes
  // save bytes to EEPROM based on struct size
  Stopwatch::ShotBytes bytes = Stopwatch::shotToBytes(shot);
  int address = shotNumber * sizeof(Stopwatch::ShotBytes);
  EEPROM.put(address, bytes);
}

bool serialRecievedDataRequest() {
  String input = Serial.readStringUntil('\n');
  if (input == "DATA_REQUEST") {
    Serial.println(input + " RECEIVED");
    return true;
  }
  return false;
}

void serialSendData() {
  Serial.println("DATA_START");
  int address = 0;
  Stopwatch::ShotBytes bytes;
  for (int i = 0; i < (EEPROM.length()/sizeof(Stopwatch::ShotBytes)); ++i) {
    EEPROM.get(address, bytes);
    // reached end of recorded data
    if (bytes.one == 0 && bytes.two == 0)
      break;
    address += sizeof(Stopwatch::ShotBytes);
    Serial.write(bytes.one);
    Serial.write(bytes.two);
    Serial.println();
  }
  Serial.println("DATA_END");
}

Stopwatch::Stopwatch s;

void setup() {
  Serial.begin(9600);
  initDraw(FPS);
}

void loop() {
  // feed the clock
  s.tick(millis());
  // detect input
  int previousButton = currentButton;
  currentButton = getButton();
  Stopwatch::Event e = Stopwatch::NONE;
  if (previousButton != currentButton && currentButton != 0 && currentButton != 5) {
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
  }

  if (Serial.available()) {
    if (serialRecievedDataRequest()) {
      e = Stopwatch::NONE;
      serialSendData();
    }
  }

  s.handleEvent(e);

  static int nextShotToSave = 0;
  if (e != Stopwatch::NONE) {
    // save shot if required
    if (s.getData().saveShots && s.getData().currentShot - 1 == nextShotToSave) {
      // complete initial EEPROM wipe if required
      // only required on button press (specifcally YES in startup confirmation menu)
      // and if we are saving shots
      // and in theory on currentShot == 0 but it suffices to check the sticky flag every time, BEFORE save
      if (!initialEraseComplete) {
        initialEraseComplete = true;
        eraseEEPROM();
      }
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