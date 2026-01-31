// Motor pin definitions 
#define MOTOR_R_IN1 1   // Direction control
#define MOTOR_R_IN2 2   // Direction control

#define MOTOR_L_IN3 3   // Direction control
#define MOTOR_L_IN4 4   // Direction control

void setupMotor() {
    pinMode(MOTOR_R_IN1, OUTPUT);
    pinMode(MOTOR_R_IN2, OUTPUT);
    pinMode(MOTOR_L_IN3, OUTPUT);
    pinMode(MOTOR_L_IN4, OUTPUT);
}

// Function with more control
void drive() {
    // Move forward
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    
    digitalWrite(MOTOR_L_IN3, HIGH);
    digitalWrite(MOTOR_L_IN4, LOW);
}

void reverse() {
    // Move backward
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, HIGH);
    
    digitalWrite(MOTOR_L_IN3, LOW);
    digitalWrite(MOTOR_L_IN4, HIGH);
}

void stop() {
    // Stop motors
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, LOW);
    
    digitalWrite(MOTOR_L_IN3, LOW);
    digitalWrite(MOTOR_L_IN4, LOW);
}

void brake() {
    // Brake motors
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, HIGH);
    
    digitalWrite(MOTOR_L_IN3, HIGH);
    digitalWrite(MOTOR_L_IN4, HIGH);
}
void turnLeft() {
    // Implementation for turning left
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    
    digitalWrite(MOTOR_L_IN3, LOW);
    digitalWrite(MOTOR_L_IN4, HIGH);
}

void turnRight() {
    // Implementation for turning right
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, HIGH);

    digitalWrite(MOTOR_L_IN3, HIGH);
    digitalWrite(MOTOR_L_IN4, LOW);
}

