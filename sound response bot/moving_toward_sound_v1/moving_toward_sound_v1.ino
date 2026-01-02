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

int micLeft, micRight;
int ampLeft, ampRight;

int amplitude;

int baselineLeft = 400;
int baselineRight = 400;

const int turnThreshold = 15;  // difference needed to turn

const int max_amplitude = 400; // FIX: larger, realistic range
const int delta = 80;     //max_amplitude / (num_LEDs + 1);

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

  ampLeft  = abs(micLeft  - baselineLeft);
  ampRight = abs(micRight - baselineRight);
  
  int diff = ampLeft - ampRight;

  int amplitude = (ampLeft + ampRight) / 2;

  if (amplitude > thresh1) {

  int speed;

  if (amplitude > thresh4)      speed = 220;
  else if (amplitude > thresh3) speed = 200;
  else if (amplitude > thresh2) speed = 160;
  else                          speed = 120;

  if (diff > turnThreshold) {
    turnLeft(speed);
  }
  else if (diff < -turnThreshold) {
    turnRight(speed);
  }
  else {
    driveForward(speed);
  }

}
else {
  stopMotors();
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
}
