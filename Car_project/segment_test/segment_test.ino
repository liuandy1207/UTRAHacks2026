// Servo
#include <Servo.h>
Servo servo;
#define servoPin 7

// Left Motor
#define IN1 2
#define IN2 3

// Right Motor
#define IN3 4
#define IN4 5

// IR Sensors
#define IR1 8

// Color Sensor

void setup() {
  Serial.begin(9600);

  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // IR Setup
  pinMode(IR1, INPUT);

  // Servo Setup
  servo.attach(servoPin);
}


// Servo Functions
void rotate(int deg) {
  servo.write(deg);
}

// Color Sensor Functions



// IR Functions
void readIR(int pin) {
  int sum = 0;
  int readings = 10;
  for (int i = 0; i < readings; i++) {
    sum += digitalRead(pin);
    delay(5);
  }
  int state = (sum > readings/2) ? HIGH : LOW;
  Serial.println(state ? "Object Detected!" : "Naw...");
  delay(100);
}

// Motor Functions
void backward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void brake() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


void loop() {

  delay(2000);
  Serial.println("Rotate Servo to 0");
  rotate(0); // low
  delay(1000);

  forward();
  delay(2000);
  brake();

  Serial.println("Rotate Servo to 90");
  rotate(90); // high

  backward();
  delay(1000);
  brake();

  forward();
  delay(1000);
  brake();

  rotate(0); // low
  delay(1000);

  backward();
  delay(1000);

  brake();

  Serial.println("End of Test");
}