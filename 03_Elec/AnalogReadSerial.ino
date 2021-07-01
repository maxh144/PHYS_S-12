
int rolling[20];
long counter = 0;


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);

  rolling[counter % 20] = sensorValue;
  double voltage = 5.0 * avg()/1023.0;

  Serial.println(int(avg()));
  //Serial.print("Voltage: ");
  //Serial.println(voltage);
  analogWrite(3, map(avg(), 0, 1024, 0, 255));

  counter++;

  delay(1);        // delay in between reads for stability
}

double avg() {

  int sum = 0;

  for (int i = 0; i < 20; i++) {
    sum += rolling[i];
  }

  return sum / 20.0;

}
