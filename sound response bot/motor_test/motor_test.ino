void setup() {
  Serial.begin(9600);
}

void loop() {
  int l = analogRead(A0);
  int r = analogRead(A1);
  Serial.print(l);
  Serial.print("  ");
  Serial.println(r);
  delay(50);}