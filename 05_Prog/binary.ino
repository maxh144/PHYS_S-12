const int LED[] = {21, 17, 16, 19};

const int button1 = 13;
const int button2 = 27;

const int stab = 200;

int count = 0;

long lastPress = 0;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i < 4; i++) {
    pinMode(LED[i], OUTPUT);
  }

  pinMode(button1, INPUT_PULLUP);

}

void loop() {

  if (!digitalRead(button1) && (millis() - lastPress > stab) ) { //used instead of delay to avoid missing presses during wait
    count++;
    lastPress = millis();
  }

  if (count > 15) {
    count = 0;
  }

  render(count);

}

void render(int total) { // Base 10 to binary converter, but instead of storing the output, it writes it to LED

  for (int i = 3; i >= 0; i--) {

    if (total - pow(2, i) >= 0) {

      total -= int(pow(2, i));

      digitalWrite(LED[3 - i], HIGH);

    }

    else {
      digitalWrite(LED[3 - i], LOW);
    }

  }

}
