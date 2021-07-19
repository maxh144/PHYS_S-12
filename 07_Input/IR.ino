const int button = 11;

double baseline = 0;
boolean state;
int result;

void setup() {
  // put your setup code here, to run once:

  pinMode(button, INPUT_PULLUP);

  Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:

  state =  !digitalRead(button);

  if (!state) {

    if (baseline == 0) { //1st time
      baseline = avg(1000);

    }

    baseline = (avg(1000) + baseline) / 2;
  }

  result = avg(1000) - baseline;

  Serial.println( -6.2*log(result) + 33.7);


}

double avg(int times) {

  long sum = 0;

  for (int i = 0; i < times; i++) {
    sum += analogRead(A2);
  }

  return sum / times;

}
