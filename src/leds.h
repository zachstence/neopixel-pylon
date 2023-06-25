#pragma once

#include "FastLED.h"

#include "config.h"

CRGB _leds[NUM_LEDS];
CRGBSet leds(_leds, NUM_LEDS);

uint8_t DEFAULT_BRIGHTNESS = (DEFAULT_BRIGHTNESS_PERCENT * 255) / 100;

void setupLeds() {
    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(DEFAULT_BRIGHTNESS);

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}
