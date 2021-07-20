#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class MomentaryButton {

  private:

    int pin;

  public:

    MomentaryButton(int thePin);
    boolean pressed();


};

class stateButton {

  public:

    stateButton(int thePin, int totalStates);
    int getState();
    void buttonPressed();

  private:

    int pin;
    int numStates;
    const static int stability = 200;
    unsigned volatile long lastPress;
    volatile int state;

    static stateButton* button;
    static void buttonPressedISR();

};

#endif
