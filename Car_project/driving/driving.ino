// Motor pin definitions for L293D/L298N
#define MOTOR1_ENA 9   // PWM pin for speed control
#define MOTOR1_IN1 8   // Direction control
#define MOTOR1_IN2 7   // Direction control

void setupMotor() {
  pinMode(MOTOR1_ENA, OUTPUT);
  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
}

// Function with more control
void controlMotor(int speed, int direction) {
  // direction: 0=stop, 1=forward, -1=reverse
  speed = abs(speed); // Ensure speed is positive
  speed = constrain(speed, 0, 255);
  
  switch(direction) {
    case 1: // Forward
      digitalWrite(MOTOR1_IN1, HIGH);
      digitalWrite(MOTOR1_IN2, LOW);
      analogWrite(MOTOR1_ENA, speed);
      break;
      
    case -1: // Reverse
      digitalWrite(MOTOR1_IN1, LOW);
      digitalWrite(MOTOR1_IN2, HIGH);
      analogWrite(MOTOR1_ENA, speed);
      break;
      
    case 0: // Stop
    default:
      digitalWrite(MOTOR1_IN1, LOW);
      digitalWrite(MOTOR1_IN2, LOW);
      analogWrite(MOTOR1_ENA, 0);
      break;
  }
}

