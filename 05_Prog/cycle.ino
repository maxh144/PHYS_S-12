const int LED[] = {21, 17, 16, 19};

const int button1 = 13;

const int wait = 1000;
const int stability = 200;

volatile boolean buttonState = LOW;
long lastPress = 0;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
  }

  pinMode(button1, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(button1), buttonPressed, FALLING);
}

void loop() {

  if (buttonState) {

    for (int i = 0; i < 4; i++) {

      digitalWrite(LED[i], HIGH);

      for (int j = i + 1; j < 4; j++) {

        digitalWrite(LED[j], HIGH);
        delay(wait);
        digitalWrite(LED[j], LOW);

      }

      digitalWrite(LED[i], LOW);
    }

  }
  else {

    for (int i = 0; i < 4; i++) {
      for (int j = i; j < 4; j++) {
        
        digitalWrite(LED[j], HIGH);
        delay(wait);
        digitalWrite(LED[j], LOW);


      }
    }

  }

}

void buttonPressed() {
  if (millis() - lastPress > stability) { // stability, don't need millis to update, just checking based on when interrupt started
    buttonState = !buttonState;
  }
  lastPress = millis();
}
