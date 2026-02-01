#include <Servo.h>

void moveServo(int angle, int timeMs) {
  int currentPos = myServo.read();
  int targetPos = currentPos + angle;

  if (targetPos > 180) targetPos = 180;
  if (targetPos < 0) targetPos = 0;

  int stepCount = abs(targetPos - currentPos);
  if (stepCount == 0) return;

  float stepDelay = (float)timeMs / stepCount;

  if (angle > 0) {
    for (int pos = currentPos; pos <= targetPos; pos++) {
      myServo.write(pos);
      delay(stepDelay);
    }
  } else {
    for (int pos = currentPos; pos >= targetPos; pos--) {
      myServo.write(pos);
      delay(stepDelay);
    }
  }
}
