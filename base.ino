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
#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define OUT 9

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

  // Color Sensor Setup
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  digitalWrite(S0, HIGH); // set frequency scaling
  digitalWrite(S1, LOW);  
}

void loop() {

}

// Servo Functions
void rotate(int deg) {
  servo.write(deg);
  // 0 puts the claw low, back leg high
  // 90 putss the claw high, back leg low
}

// Color Sensor Functions

// Calibration Values
int redMin = 25; 
int redMax = 267; 
int greenMin = 26; 
int greenMax = 231; 
int blueMin = 20; 
int blueMax = 216; 

int identifyColor() {
  int r = getAverage(LOW, LOW);
  int g = getAverage(HIGH, HIGH);
  int b = getAverage(LOW, HIGH);

  r = constrain(map(r, redMin, redMax, 255, 0), 0, 255);
  g = constrain(map(g, greenMin, greenMax, 255, 0), 0, 255);
  b = constrain(map(b, blueMin, blueMax, 255, 0), 0, 255);
  
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);

  Serial.print(" - Color: ");
  if (r < 50 && g < 50 && b < 50) {
    Serial.println("BLACK");
  } else if (r > 200 && g > 200 && b > 200) {
    Serial.println("WHITE");
  } else if (r > g && r > b) {
    Serial.println("RED");
  } else if (g > r && g > b) {
    Serial.println("GREEN");
  } else if (b > r && b > g) {
    Serial.println("BLUE");
  } else {
    Serial.println("UNCERTAIN");
  }
  return 0;
}

int getAverage(int s2State, int s3State) {
  int sum = 0;
  int readings = 50;

  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  for (int i = 0; i < readings; i++) {
    sum += pulseIn(OUT, LOW);
  }
  return sum / readings;
}


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
