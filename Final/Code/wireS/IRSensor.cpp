#include "IRSensor.h"

IRSensor::IRSensor(int thePin, int numSamples) {

  pin = thePin;
  samples = numSamples;


}

void IRSensor::init() {

  pinMode(pin, INPUT);
  baseline = avg();

}

double IRSensor::getDist() { //cm

  double num = avg();

  return -20.0 * log(num) + 156.0;

}

double IRSensor::avg() {

  double sum = 0;

  for (int i = 0; i < samples; i++) {

    sum += limit(analogRead(pin)/4.0 - baseline);

  }

  return double(sum) / samples;

}

void IRSensor::setNumSamples(int numSamples) {

  samples = numSamples;

}

double IRSensor::limit(double n) {

  if (n > 0.0) {

    return n;

  }
  else {

    return 0.0001;

  }

}
