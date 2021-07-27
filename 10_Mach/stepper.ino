const int stepPin = 3;
const int dirPin = 2;

const int stepPin2 = 5;
const int dirPin2 = 4;

int x = -1250;
int y = 0;
int dist;

double func[4]; //H shift, V shift, H offset, V offset

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);

  digitalWrite(dirPin, LOW);

  delay(5000);

  for (int i = 0; i < 1250; i++) {

    digitalWrite(stepPin2, LOW);
    delay(1);
    digitalWrite(stepPin2, HIGH);
    delay(1);

  }

  delay(5000);

  Serial.begin(0);              //This is the USB serial.
  Serial.setTimeout(20);        //Set wait time for serial data to 20ms (default 1 sec).
  while (!Serial) {             //Wait until Serial wakes up.
    ;
  }

  Serial.println("ready");


  getSer();

}

void loop() {

  if (x > 1250) {

    digitalWrite(dirPin, HIGH);

    for (int i = 0; i < 2500; i++) {

      digitalWrite(stepPin, LOW);
      delay(1);
      digitalWrite(stepPin, HIGH);
      delay(1);

    }

    digitalWrite(dirPin, LOW);
    x = -1250;

    getSer();

  }

  digitalWrite(stepPin, LOW);
  delay(1);
  digitalWrite(stepPin, HIGH);
  delay(1);

  dist =  getY(x) - y;

  if (dist > 0) {
    digitalWrite(dirPin2, LOW);

  }
  else {
    digitalWrite(dirPin2, HIGH);
  }

  for (int i = 0; i < abs(dist); i++) {

    digitalWrite(stepPin2, LOW);
    delay(1);
    digitalWrite(stepPin2, HIGH);
    delay(1);

  }

  y += dist;
  x++;
}

void getSer() {

  while (!Serial.available() ) {            //Loop and do nothing until there is a serial character received.
    ;
  }

  Serial.println("Input (dbl): HS VS HO VO");

  for (int i = 0; i < 4; i++) {
    func[i] = Serial.parseFloat();
  }
}

int getY(int theX) {
  
  int result = int(func[1] * sin( (theX / func[0]) - func[2]) + func[3]);
  
  if(result > 1250) result = 1250;
  if(result < -1250) result = -1250;

  return result;
}
