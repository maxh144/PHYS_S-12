
const int analog_pin = A3;
const int tx_pin = A1;

const int thresh = -15; // diff per material
const int retThresh = -3;
const int objHeight = 14.5; // In cm

double result;
double baseline;
long interval; // time object is in plates
double vel = 0; // velocity of obj
boolean counting = false; // is the timer counting a spike


void setup() {
  pinMode(tx_pin, OUTPUT);

  baseline = tx_rx();

  Serial.begin(9600);
}


void loop() {

  result = tx_rx() - baseline;

  if (result <= thresh && !counting) { // If we are out of the old cycle and cross the threshold, start the timer
    interval = millis();
    counting = true;

  }
  else if (result <= thresh && counting) { // If we are still past the threshold and on the same cycle, update the speed

    vel = ((5.0 + objHeight) * 10.0) / (millis() - interval); // 5 is height of plates, unit conversion

  }
  if (result >= retThresh && counting) { // can only reset counting once system has returned to normal

    counting = false;

  }

  //Serial.print("Reading: ");
  Serial.println(result);
  //Serial.print("m/s: ");
  //Serial.println(vel);



}


double tx_rx() {

  int read_high;
  int read_low;
  long int sum;
  int N_samples = 100;    //Number of samples to take.  Larger number slows it down, but reduces scatter.
  long start;

  sum = 0;

  for (int i = 0; i < N_samples; i++) {

    digitalWrite(tx_pin, HIGH);             //Step the voltage high on conductor 1.
    read_high = analogRead(analog_pin);        //Measure response of conductor 2.


    start = micros();
    while (micros() - start < 100) {}


    digitalWrite(tx_pin, LOW);              //Step the voltage to zero on conductor 1.
    read_low = analogRead(analog_pin);         //Measure response of conductor 2.
    sum += read_high - read_low;

  }

  return sum / N_samples;
}
