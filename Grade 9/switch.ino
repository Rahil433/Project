// Define pin constants
const int BUTTON_PIN = 4;

const int RED_LED = 12;
const int GREEN_LED = 14;
const int BLUE_LED = 27;

void setup() {
  // Set LED pins as OUTPUT
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Set push button pin as INPUT_PULLUP
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Turn OFF all colours initially
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void loop() {
  // Check if button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Turn ON Green colour
    digitalWrite(GREEN_LED, LOW);
  } 
  else {
    // Turn OFF Green LED
    digitalWrite(GREEN_LED, HIGH);
  }
}
