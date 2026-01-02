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

const int smoothFactor = 8;

float smoothLeft = 0;
float smoothRight = 0;

int micLeft, micRight;
int ampLeft, ampRight;

int amplitude;

int baselineLeft = 400;
int baselineRight = 400;

const int turnThreshold = 35;  // difference needed to turn

const int max_amplitude = 400; // FIX: larger, realistic range
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
  micLeft = analogRead(micpinLeft);
  micRight = analogRead(micpinRight);

  // track baselines independently
  baselineLeft  = (baselineLeft * 9 + micLeft) / 10;
  baselineRight = (baselineRight * 9 + micRight) / 10;

  int rawLeft  = abs(micLeft  - baselineLeft);
  int rawRight = abs(micRight - baselineRight);

  smoothLeft  = (smoothLeft  * (smoothFactor - 1) + rawLeft)  / smoothFactor;
  smoothRight = (smoothRight * (smoothFactor - 1) + rawRight) / smoothFactor;

  ampLeft  = smoothLeft;
  ampRight = smoothRight;
  
  int diff = ampLeft - ampRight;

  int amplitude = (ampLeft + ampRight) / 2;
  if (amplitude < 20) amplitude = 0;

  if (amplitude > thresh2) {

  int baseSpeed;

  if (amplitude > thresh5)      baseSpeed = 150;
  else if (amplitude > thresh4) baseSpeed = 100;
  else                          stopMotors();
  
  float Kp = 0.8; // tuning parameter
  
  int correction = Kp * diff;
  correction = constrain(correction, -100, 100);

  int leftSpeed = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(AIN1, leftSpeed);
  digitalWrite(AIN2, LOW);

  analogWrite(BIN1, rightSpeed);
  digitalWrite(BIN2, LOW);
  
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
  Serial.print(ampLeft);
  Serial.print(" R: ");
  Serial.print(ampRight);
  Serial.print(" diff: ");
  Serial.println(diff);
}}

