// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Calibration Values (Using your provided values)
int redMin = 25; 
int redMax = 267; 
int greenMin = 26; 
int greenMax = 231; 
int blueMin = 20; 
int blueMax = 216; 

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set Frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // 1. Get averaged Pulse Widths
  int avgRedPW = getAveragePW(LOW, LOW);   // Red
  int avgGreenPW = getAveragePW(HIGH, HIGH); // Green
  int avgBluePW = getAveragePW(LOW, HIGH);  // Blue

  // 2. Map to 0-255 scale
  // Note: we use constrain to ensure values stay within 0-255
  int r = constrain(map(avgRedPW, redMin, redMax, 255, 0), 0, 255);
  int g = constrain(map(avgGreenPW, greenMin, greenMax, 255, 0), 0, 255);
  int b = constrain(map(avgBluePW, blueMin, blueMax, 255, 0), 0, 255);

  // 3. Print the RGB Values
  Serial.print("R: "); Serial.print(r);
  Serial.print(" G: "); Serial.print(g);
  Serial.print(" B: "); Serial.print(b);

  // 4. Determine Color Name
  identifyColor(r, g, b);

  delay(500); // Small pause between full scans
}

// Function to take 100 samples and return the average
int getAveragePW(int s2State, int s3State) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);
  
  long total = 0; // Use 'long' to prevent overflow when adding 100 numbers
  int samples = 100;
  
  for (int i = 0; i < samples; i++) {
    total += pulseIn(sensorOut, LOW);
  }
  
  return total / samples;
}

void identifyColor(int r, int g, int b) {
  Serial.print(" - Color: ");
  
  // Basic Threshold check
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
}