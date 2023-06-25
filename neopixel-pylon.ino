#include "FastLED.h"

#include "src/leds.h"

void setup() {
  setupLeds();
}

void loop() {
  leds.fill_solid(CRGB::Red);
  FastLED.show();
}
