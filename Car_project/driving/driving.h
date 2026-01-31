#ifndef DRIVING_H
#define DRIVING_H
// Motor pin definitions 
#define MOTOR_R_IN1 1   // Direction control
#define MOTOR_R_IN2 2   // Direction control
#define MOTOR_L_IN3 3   // Direction control
#define MOTOR_L_IN4 4   // Direction control

// Function declarations
void setupMotor();
void drive();
void reverse();
void stop();
void brake();
void turnLeft();
void turnRight();

#endif