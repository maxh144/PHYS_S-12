#ifndef IRSENSOR_H
#define IRSENSRO_H

#include <Arduino.h>

class IRSensor {

  private:

    double avg();
    double limit(double n);

    int pin;
    int baseline = 0;
    int samples;

  public:

    IRSensor(int thePin, int numSamples);
    void init();
    double getDist();
    void setNumSamples(int numSamples);




};

#endif
