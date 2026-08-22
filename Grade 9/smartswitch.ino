#include <Adafruit_NeoPixel.h>

#define LED_PIN 22
#define BUTTON_PIN 4
#define NUM_LEDS 8

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {

  // Button pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    strip.fill(strip.Color(0, 255, 0));  // Green ON
    strip.show();
  }

  // Button released
  else {
    strip.clear();  // OFF
    strip.show();
  }
}
