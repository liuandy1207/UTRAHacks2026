#include <Servo.h>

Servo myservo;

void setupServo() {
  myservo.attach(7);  // Attach servo to pin 7
}

// Function to move servo to specific angle
void moveServo(int angle) {
  angle = constrain(angle, 0, 180);  // Limit to servo range
  myservo.write(angle);
}