const int RED= 12;
const int GREEN= 14;
void setup() {
 // put your setup code here, to run once:
 pinMode(RED, OUTPUT);
 pinMode(GREEN, OUTPUT);
}
void loop() {
 // put your main code here, to run repeatedly:
digitalWrite(RED, LOW);
delay(1000);
digitalWrite(RED, HIGH);
delay(1000);
digitalWrite(GREEN, LOW);
delay(1000);
digitalWrite(GREEN, HIGH);
delay(1000);
}
