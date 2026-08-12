

const int RED= 12;
void setup() {
 // put your setup code here, to run once:
 pinMode(RED, OUTPUT);
 }
void loop() {
 // put your main code here, to run repeatedly:
digitalWrite(RED, LOW);
delay(1000);
digitalWrite(RED, HIGH);
delay(1000);
}
