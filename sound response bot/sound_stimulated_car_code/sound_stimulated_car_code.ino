const int micpin = A0;
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

int mic;

int baseline = 512;           
int amplitude;

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
  mic = analogRead(micpin);

  // FIX: dynamically track baseline
  baseline = (baseline * 9 + mic) / 10;

  amplitude = abs(mic - baseline);
  Serial.println(amplitude);

  if (amplitude > thresh6) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    driveForward(220);
    digitalWrite(buzzerpin, HIGH);
  }
  
  else if (amplitude > thresh5) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    driveForward(180);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh4) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    driveForward(150);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh3) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    driveForward(120);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh2) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    driveForward(100);
    digitalWrite(buzzerpin, LOW);
  }
  
  else if (amplitude > thresh1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    stopMotors();
    digitalWrite(buzzerpin, LOW);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    stopMotors();
    digitalWrite(buzzerpin, LOW);
  }
}

