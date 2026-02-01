const int TRIG_PIN = 3;
const int ECHO_PIN = 4;

void setup() {
  Serial.begin(9600);       // For debugging/output
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  int objectClose = checkDistance();
  Serial.println(objectClose);  // Prints 0 or 1
  delay(200);                   // Small delay to avoid flooding
}

int checkDistance() {
  // Send a 10µs pulse to trigger
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pulse duration
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  float distance = duration * 0.034 / 2;

  // Return 1 if object is 10cm or less, otherwise 0
  return distance;
  // if (distance <= 10) {
  //   return 1;
  // } else {
  //   return 0;
  // }
}
