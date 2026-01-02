const int micpin = A0;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 12;
const int led5 = 13;
const int buzzerpin = 8;

const int num_LEDs = 5;        // FIX: you have 5 LEDs, not 6

int mic;

int baseline = 400;            // FIX: no longer const
int amplitude;

const int max_amplitude = 600; // FIX: larger, realistic range
const int delta = max_amplitude / (num_LEDs + 1);

const int thresh1 = delta; 
const int thresh2 = thresh1 + 80; 
const int thresh3 = thresh2 + 100;
const int thresh4 = thresh3 + 120;
const int thresh5 = thresh4 + 20;
const int thresh6 = thresh5 + 30;

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

