#include "button.h"


MomentaryButton::MomentaryButton(int thePin) {

  pin = thePin;
  pinMode(pin, INPUT_PULLUP);

}

boolean  MomentaryButton::pressed() {

  return !digitalRead(pin);

}

stateButton::stateButton(int thePin, int totalStates) {

  pin = thePin;
  numStates = totalStates;
  state = 0;

  button = this;

  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), buttonPressedISR, FALLING);

}

int stateButton::getState() {

  return state;

}

void stateButton::buttonPressed() {

  if (millis() - lastPress > stability) { // stability, don't need millis to update, just checking based on when interrupt started
    state++;
    state = state % numStates;
  }
  lastPress = millis();

}

stateButton* stateButton::button;

void stateButton::buttonPressedISR() {

  if (button != 0) {

    button->buttonPressed();

  }

}
