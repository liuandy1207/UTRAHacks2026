// Define pin connections
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define sensorOut 12

// Variables for color pulse width measurements
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  // Set S0-S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set sensorOut as input
  pinMode(sensorOut, INPUT);
  
  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  
  Serial.begin(9600);
}

void loop() {
  // Read Red component
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);
  delay(100);
  
  // Read Green component
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);
  delay(100);
  
  // Read Blue component
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);
  
  // Print RGB values
  Serial.print("R = ");
  Serial.print(redFrequency);
  Serial.print("  G = ");
  Serial.print(greenFrequency);
  Serial.print("  B = ");
  Serial.println(blueFrequency);
  
  delay(1000);
}

