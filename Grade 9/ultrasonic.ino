#include <ESP32Servo.h>
#include <Adafruit_NeoPixel.h>

// Ultrasonic Sensor Pins
const int trigPin = 15;
const int echoPin = 13;

// Smart Light (NeoPixel LED Strip) Setup on Pin 21
#define LED_PIN   21
#define NUM_LEDS  7
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Tri-Color (RGB) LED Pins (Common Anode: HIGH = OFF, LOW = ON)
const int redPin   = 12;
const int greenPin = 14;
const int bluePin  = 27;

// Servo Pins & Objects
const int panPin  = 25;
const int tiltPin = 26;
Servo panServo;
Servo tiltServo;

// Distance threshold in centimeters (triggers if object is closer than 30 cm)
const int distanceThreshold = 30; 

void setup() {
  Serial.begin(115200);
  delay(2000); // Boot delay to stabilize sensors

  // Ultrasonic setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // NeoPixel Smart Light setup - Fixed startup glow
  strip.begin();
  strip.clear();        // Clear any random startup data in memory
  strip.show();         // Push the 'off' state immediately

  // RGB LED setup
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Attach Servos
  panServo.attach(panPin);
  tiltServo.attach(tiltPin);

  // Set everything to OFF / Center position initially
  turnEverythingOff();
}

void loop() {
  long distance = getDistance();
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is detected within range
  if (distance > 2 && distance <= distanceThreshold) {
    Serial.println("Object Sensed! Running 6-second sequence...");
    runActiveSequence();
    
    Serial.println("Sequence finished. Turning everything OFF.");
    turnEverythingOff();
    
    // Short delay before sensing again so it doesn't instantly re-trigger
    delay(1000); 
  }

  delay(100); // Small delay between ultrasonic pings
}

// Function to measure distance using HC-SR04
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  long cm = duration * 0.034 / 2;
  return cm;
}

// Runs for 6 seconds: changes colors and moves pan/tilt side-to-side
void runActiveSequence() {
  unsigned long startTime = millis();
  unsigned long duration = 6000; // 6 seconds

  int panAngle = 45;
  int panStep = 5;
  int colorState = 0;
  unsigned long lastColorChange = 0;

  while (millis() - startTime < duration) {
    // 1. Move Pan & Tilt side-to-side smoothly
    panServo.write(panAngle);
    tiltServo.write(map(panAngle, 45, 135, 60, 120));

    panAngle += panStep;
    if (panAngle >= 135 || panAngle <= 45) {
      panStep = -panStep;
    }

    // 2. Cycle colors every 500ms
    if (millis() - lastColorChange >= 500) {
      lastColorChange = millis();
      colorState = (colorState + 1) % 3;

      if (colorState == 0) {
        setRGB(LOW, HIGH, HIGH);      // Tri-color LED: Red (LOW = ON)
        setStripColor(255, 0, 0);     // Smart Light Strip: Red
      } else if (colorState == 1) {
        setRGB(HIGH, LOW, HIGH);      // Tri-color LED: Green
        setStripColor(0, 255, 0);     // Smart Light Strip: Green
      } else {
        setRGB(HIGH, HIGH, LOW);      // Tri-color LED: Blue
        setStripColor(0, 0, 255);     // Smart Light Strip: Blue
      }
    }

    delay(30);
  }
}

// Helper function to set all 7 NeoPixels to a single color
void setStripColor(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(r, g, b));
  }
  strip.show();
}

// Helper function for Common Anode RGB LED (HIGH = OFF, LOW = ON)
void setRGB(int r, int g, int b) {
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}

// Turns off both lights and resets servos to center (90 degrees)
void turnEverythingOff() {
  setStripColor(0, 0, 0);       // Turn off NeoPixel strip
  setRGB(HIGH, HIGH, HIGH);     // Turn OFF Tri-color LED (HIGH = OFF)
  panServo.write(90);
  tiltServo.write(90);
}
