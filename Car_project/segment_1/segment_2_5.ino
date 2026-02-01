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

// Echo Sensor
#define TRIG 8
#define ECHO 6

// Color Sensor
#define S0 13
#define S1 12
#define S2 11
#define S3 10
#define OUT 9

// Calibration Values
int redMin = 15,  redMax = 24;
int greenMin = 15, greenMax = 40;
int blueMin = 9, blueMax = 27;

// Calibration Values 2
int redMin2 = 9,  redMax2 = 24;
int greenMin2 = 16, greenMax2 = 30;
int blueMin2 = 15, blueMax2 = 30;

void setup() {
  Serial.begin(115200);

  // Motor Setup
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

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

  // Echo Sensor Setup
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

// Servo Functions
void rotate(int deg) {
  servo.write(deg);
  // 0 puts the claw low, back leg high
  // 90 puts the claw high, back leg low
}

// Color Sensor Functions
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
    return 4;
  } else if (r > 200 && g > 200 && b > 200) {
    Serial.println("WHITE");
    return 0;
  } else if (r > g && r > b) {
    Serial.println("RED/BROWN");
    return 1;
  } else if (g > r && g > b) {
    Serial.println("GREEN");
    return 2;
  } else if (b > r && b > g) {
    Serial.println("BLUE");
    return 3;
  } else {
    Serial.println("UNCERTAIN");
  }
  return 0;
}

// Use for elevated!!!
int identifyColor2() {
  int r = getAverage(LOW, LOW);
  int g = getAverage(HIGH, HIGH);
  int b = getAverage(LOW, HIGH);

  r = constrain(map(r, redMin2, redMax2, 255, 0), 0, 255);
  g = constrain(map(g, greenMin2, greenMax2, 255, 0), 0, 255);
  b = constrain(map(b, blueMin2, blueMax2, 255, 0), 0, 255);
  
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);

  Serial.print(" - Color: ");
  if (r < 50 && g < 50 && b < 50) {
    Serial.println("BLACK");
    return 4;
  } else if (r > 180 && g > 180 && b > 180) {
    Serial.println("WHITE");
    return 0;
  } else if (r > g && r > b) {
    Serial.println("RED/BROWN");
    return 1;
  } else if (g > r && g > b) {
    Serial.println("GREEN");
    return 2;
  } else if (b > r && b > g) {
    Serial.println("BLUE");
    return 3;
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

// Echo Sensor Code
int checkDistance() {
  // clear it
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // get the reading
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH);
  float distance = duration * 0.034 / 2;
  return distance;
}

/* IR Functions
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
*/

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

void turnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

//new function end
void moveAndCheckColor(int tColour, char dir, int bg) {
  bool begin = true;
  int almost90 = 2000; // TODO: fix
  int step = int(almost90/6);
  int colour = identifyColor();
  while(colour != 3 || colour != bg){ //3= brown
    Serial.println("checked");
    if (colour == tColour){
      Serial.println("straight");
      begin = true;
      forward();
      delay(500);
    }
    else if (begin){
      Serial.println("command");

      if(dir == 'l'){
        turnLeft();//amount to get to just under 180deg left
      }
      else{
        turnRight();//amount to get to just under 180deg left
      }
      delay(almost90); //dir
      begin = false;
    }
    else{
      if(dir == 'l'){
        turnRight(); //dir
      }
      else{
        turnLeft();
      }
      delay(step);
    }
    int dist = checkDistance();
    if (dist < 20){
      return;
    }
    colour = identifyColor();
  }
}

void moveAndCheckColor2(int tColour, char dir, int bg) {
  bool begin = true;
  int almost90 = 2000; // TODO: fix
  int step = int(almost90/6);
  int colour = identifyColor2();
  while(colour != 3 || colour != bg){ //3= brown
    Serial.println("checked");
    if (colour == tColour){
      Serial.println("straight");
      begin = true;
      forward();
      delay(500);
    }
    else if (begin){
      Serial.println("command");

      if(dir == 'l'){
        turnLeft();//amount to get to just under 180deg left
      }
      else{
        turnRight();//amount to get to just under 180deg left
      }
      delay(almost90); //dir
      begin = false;
    }
    else{
      if(dir == 'l'){
        turnRight(); //dir
      }
      else{
        turnLeft();
      }
      delay(step);
    }
    int dist = checkDistance();
    if (dist < 20){
      return;
    }
    colour = identifyColor2();
  }
}

// =================================

void loop() {
  moveAndCheckColor(2, 'l', 0);

  // pick up cube
   backward();
   delay(2000);
   turnRight();
   delay(1000);
   forward();
   delay(2500);
   brake();
   delay(1000);
   rotate(30);
   delay(500);
   rotate(60);
   delay(500);
   rotate(90);
   delay(500);

   turnLeft();
   delay(2000);

  int c1 = identifyColor2();
  while (c1 != 1) {
      Serial.println(c1);
      forward();
      delay(50);
      c1 = identifyColor2();
   }

  // drop box
  forward();
  delay(250);
  rotate(60);
  delay(500);
  rotate(30);
  delay(500);
  rotate(0);
  delay(500);
  turnRight();
  delay(2400);

  forward(1200); //

  moveAndCheckColor(4, 'l', 1);
  
  int c2 = identifyColor();
  while (c2 != 4) {
    forward(50);
    delay(50);
    c1 = identifyColor();
  }
  brake();
  delay(10000);
}

