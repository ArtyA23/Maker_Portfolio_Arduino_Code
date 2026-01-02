
// declare constant variables for pins
int mic; // variable for mic analogRead

void setup() {
  // put your setup code here, to run once:
  pinMode(mic,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  mic = analogRead(A0);
  Serial.println(mic);
}