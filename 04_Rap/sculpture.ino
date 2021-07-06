#include <Servo.h>

const int PIN_A = 3;
Servo myServo;

int angle;
int wait;

void setup() {
  // put your setup code here, to run once:

  myServo.attach(PIN_A);
  myServo.write(90);
  delay(1000);
    
}

void loop() {
  // put your main code here, to run repeatedly:

  angle = analogRead(A1);
  wait = analogRead(A2) + 500; //delay is at least 500ms


  myServo.write(90 + map(angle, 0, 1023, 0, 90));
  
  delay(wait);

  myServo.write(90 - map(angle, 0, 1023, 0, 90));

  delay(wait);

}
