int red = 9;
int green = 10;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(1000);

  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  delay(1000);
}
