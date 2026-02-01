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
void obstacle_avoidance_sequence() {

  // 1. Follow red until obstacle (< 10 cm)
  if (checkDistance() < 10) {


    // 2. Turn right for 10 seconds
    turnRight();
    delay(10000);
    brake();

    // 3. Check distance again
    if (checkDistance() >= 10) {

      // No obstacle
      forward();
      delay(10000);
      brake();

    } else {

      // Obstacle still present
      turnRight();
      delay(10000);
      brake();

      forward();
      delay(10000);
      brake();
    }

    // 4. Turn left for 10 seconds to parallel with red line
    turnLeft();
    delay(10000);
    brake();
    // 5. turn left for 10 seconds to face red line
    turnLeft();
    delay(10000); 
    brake();
    
    // 5. Move forward until object is at red, stopping to poll every 0.25s
    while (identifyColor() != 1) {
      forward();
      delay(250);
    }
    brake();

    // 6. Turn left for 10 seconds
    turnLeft();
    delay(10000);
    brake();
  }
}
