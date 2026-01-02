const int micpinLeft = A0;
const int micpinRight = A1;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int BIN1 = 5;
const int BIN2 = 6;
const int buzzerpin = 8;
const int AIN1 = 9;
const int AIN2 = 10;
const int led4 = 12;
const int led5 = 13;
const int num_LEDs = 5;       

const int noiseFloor = 300;    // ignore mic noise
const int turnSpeed  = 120;
const int driveSpeed = 150;

int amplitude;

int baselineLeft = 512;
int baselineRight = 512;

const int turnThreshold = 100;  // difference needed to turn; ie. how much louder one side must be

const int max_amplitude = 512; // FIX: larger, realistic range
const int delta = 100;     //max_amplitude / (num_LEDs + 1);

const int thresh1 = delta; //red LED
const int thresh2 = thresh1 + 150; //yellow LED
const int thresh3 = thresh2 + 150; //green LED
const int thresh4 = thresh3 + 20;  //blue LED
const int thresh5 = thresh4 + 20;  //violet LED
const int thresh6 = thresh5 + 5;   //buzzer

void stopMotors() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void turnLeft(int speedVal) {
  analogWrite(AIN1, speedVal);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  analogWrite(BIN2, speedVal);
}

void turnRight(int speedVal) {
  digitalWrite(AIN1, LOW);
  analogWrite(AIN2, speedVal);
  analogWrite(BIN1, speedVal);
  digitalWrite(BIN2, LOW);
}

void driveForward(int speedVal) {
  analogWrite(AIN1, speedVal);
  digitalWrite(AIN2, LOW);
  analogWrite(BIN1, speedVal);
  digitalWrite(BIN2, LOW);
}

void driveBackward(int speedVal) {
  analogWrite(AIN1, LOW);
  digitalWrite(AIN2, speedVal);
  analogWrite(BIN1, LOW);
  digitalWrite(BIN2, speedVal);
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int left  = analogRead(micpinLeft);
  int right = analogRead(micpinRight);

  int leftAmp  = abs(left - baselineLeft);
  int rightAmp = abs(right - baselineRight);

  int diff = leftAmp - rightAmp;
  int avg  = (leftAmp + rightAmp) / 2;

  amplitude = avg;

  // --- QUIET: STOP ---
  if (avg < noiseFloor) {
    stopMotors();
    return;
  }

  // --- TURN FIRST ---
  if (diff > turnThreshold) {
    // sound stronger on left → turn left
    turnRight(turnSpeed);
  }
  else if (diff < -turnThreshold) {
    // sound stronger on right → turn right
    turnLeft(turnSpeed);
  }
  else {
    // sound centered → drive forward
    driveForward(driveSpeed);
  }
  
  Serial.println(amplitude);

  if (amplitude > thresh6) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(buzzerpin, HIGH);
  }
  
  else if (amplitude > thresh5) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh4) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh3) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh2) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(buzzerpin, LOW);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(buzzerpin, LOW);
  }
  Serial.print("L: ");
  Serial.print(leftAmp);
  Serial.print(" R: ");
  Serial.print(rightAmp);
  Serial.print(" diff: ");
  Serial.println(diff);
}

