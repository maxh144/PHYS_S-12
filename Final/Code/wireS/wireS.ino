#include <Wire.h>
#include "IRSensor.h"

volatile int volt;
volatile int dist;


IRSensor IR(A0, 500);

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event

  analogReadResolution(12);

  IR.init();

}

void loop() {

  volt = analogRead(A2);

  dist = int(IR.getDist() * 100.0);

}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {

  Wire.write(highByte(volt)); // respond with message of 6 bytes
  Wire.write(lowByte(volt));

  Wire.write(highByte(dist)); // respond with message of 6 bytes
  Wire.write(lowByte(dist));

}
