#include "screen.h"
#include "IRSensor.h"

screen test = screen(500);
IRSensor IR = IRSensor(A0, 1000);
double sensorValue;

void setup() {
  Serial.begin(9600);
  
  test.init();
  IR.init();
}

void loop() {
  double ran = random(0, 1000) / 100.0;
  sensorValue = round(IR.getDist()) / 100.0;
  test.update(sensorValue, ran, ran, ran);
}
