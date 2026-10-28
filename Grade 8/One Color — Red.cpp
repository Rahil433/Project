int red = 9;

void setup() {
  pinMode(red, OUTPUT);
}

void loop() {
  digitalWrite(red, LOW);
  delay(1000);
  digitalWrite(red, HIGH);
  delay(1000);
}
