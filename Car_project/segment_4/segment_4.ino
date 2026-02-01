// 1. go straight by following the black line (straight)using the move and check color function to maintain black path turning left to check

// 2. when you see green or no longer see black, checking right to check if green is present if green present, go to next stage

// 4. use the move and check color function to maintain green path until see black, checking right to check if black is present, if black present, go to next stage

// 5. use the move and check color function to maintain black path until, checking right to the end.
/*void loop() {
  delay(2000);
  moveAndCheckColor(1, 'r', 0); //looking for red, turning left

}this is sample code for a stage of checking if the color is there, then moving and checking color*/


#define WHITE 0
#define RED   1
#define GREEN 2
#define BLUE  3
#define BLACK 4


/// Servo
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



void setup() {
  Serial.begin(9600);

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

  servo.write(0);
}


// Color Sensor Functions

// Calibration Values
int redMin = 11,  redMax = 28;
int greenMin = 11, greenMax = 32;
int blueMin = 11, blueMax = 30;

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

// Calibration Values 2
int redMin2 = 17,  redMax2 = 31;
int greenMin2 = 20, greenMax2 = 35;
int blueMin2 = 18, blueMax2 = 33;

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

//new function
void obstacle_avoidance_sequence() {

  // 1. Follow red until obstacle (< 10 cm)
  if (checkDistance() < 10) {


    // 2. Turn right for 10 seconds
    turnLeft();
    delay(1900);
    brake();

    // 3. Check distance again
    if (checkDistance() >= 10) {

      // No obstacle
      forward();
      delay(3500);
      brake();

    } else {

      // Obstacle still present
      turnLeft();
      delay(2000);
      brake();

      forward();
      delay(3500);
      brake();
    }

    // 4. Turn left for 10 seconds to parallel with red line
    turnRight();
    delay(1900);
    brake();

    forward();
    delay(3500);
    brake();

    // 5. turn left for 10 seconds to face red line
    turnRight();
    delay(1900); 
    brake();
    
    // 5. Move forward until object is at red, stopping to poll every 0.25s
    while (identifyColor() != 1) {
      forward();
      delay(250);
    }
    brake();

    // 6. Turn left for 10 seconds
    turnLeft();
    delay(1000);
    brake();
  }
}

//new function end
void moveAndCheckColor(int tColour, char dir, int bg) {
  forward();
  delay(500);
  bool begin = true;
  int almost90 = 2000; // TODO: fix
  int step = int(almost90/10);
  int colour = identifyColor();
  forward();
  delay(500);
  while(colour != 3 && colour != bg){ //3= brown
    int colour = identifyColor();
    if (colour == tColour){
      begin = true;
      forward();
        delay(500);
    }
    else if (begin){
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
  }
}
findBall(){
  turnLeft();
  int almost90 = 2500; 
  delay(almost90);
  int minDist = 1000;
  int totalTurn = 0;
  while(totalTurn < almost90*2){
    
  }
  //lowly turn right
}

void loop() {
  moveforward();
  delay(2000);
  moveAndCheckColor(BLACK, 'r', RED);

  moveAndCheckColor(GREEN, 'l', RED);

  moveAndCheckColor(BLACK, 'r', RED)
}
