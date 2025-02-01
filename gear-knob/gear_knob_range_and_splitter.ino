#include <Joystick.h>

#define LED_PIN 17

int RANGE_PIN = 2;
int SPLIT_PIN = 3;

int RANGE_BTN_IDX = 0;
int SPLIT_BTN_IDX = 1;

int rangeState;
int splitState;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_GAMEPAD, 2, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);

void buttonPressRelease(int button_id, int state) {
  if (state == HIGH) {
    Joystick.releaseButton(button_id);
    digitalWrite(LED_PIN, LOW);
  }
  else {
    Joystick.pressButton(button_id);
    digitalWrite(LED_PIN, HIGH);
  }
}

void setup() {
  Joystick.begin();
  pinMode(LED_PIN, OUTPUT);

  // Range
  pinMode(RANGE_PIN, INPUT_PULLUP);
  rangeState = digitalRead(RANGE_PIN);
  buttonPressRelease(RANGE_BTN_IDX, rangeState);

  // Split
  pinMode(SPLIT_PIN, INPUT_PULLUP);
  splitState = digitalRead(SPLIT_PIN);
  buttonPressRelease(SPLIT_BTN_IDX, splitState);
}

void loop() {
  // Range
  int rangeRead = digitalRead(RANGE_PIN);
  if(rangeRead != rangeState) {
    rangeState = rangeRead;
    buttonPressRelease(RANGE_BTN_IDX, rangeRead);
  }

  // Split
  int splitRead = digitalRead(SPLIT_PIN);
  if(splitRead != splitState) {
    splitState = splitRead;
    buttonPressRelease(SPLIT_BTN_IDX, splitRead);
  }
}