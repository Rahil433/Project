#include <Adafruit_NeoPixel.h>

#define LED_PIN 22
#define NUM_LEDS 8   // Change according to your LED count

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
}

void loop() {
  // Red
  strip.fill(strip.Color(255, 0, 0));
  strip.show();
  delay(1000);

  // Green
  strip.fill(strip.Color(0, 255, 0));
  strip.show();
  delay(1000);

  // Blue
  strip.fill(strip.Color(0, 0, 255));
  strip.show();
  delay(1000);

  // Yellow
  strip.fill(strip.Color(255, 255, 0));
  strip.show();
  delay(1000);

  // Purple
  strip.fill(strip.Color(255, 0, 255));
  strip.show();
  delay(1000);

  // White
  strip.fill(strip.Color(255, 255, 255));
  strip.show();
  delay(1000);
}
