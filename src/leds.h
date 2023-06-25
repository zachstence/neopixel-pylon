#pragma once

#include "FastLED.h"

#include "config.h"

CRGB _leds[NUM_LEDS];
CRGBSet leds(_leds, NUM_LEDS);
auto zones = new CRGBSet*[NUM_ZONES];

uint8_t DEFAULT_BRIGHTNESS = (DEFAULT_BRIGHTNESS_PERCENT * 255) / 100;

void setupLeds() {
    for (int i = 0; i < NUM_ZONES; i++) {
        int start = i * LEDS_PER_ZONE;
        int end = start + LEDS_PER_ZONE;
        Serial.println("Zone");
        Serial.print(start);
        Serial.print(" ");
        Serial.print(end);
        CRGBSet* zone = new CRGBSet(leds, start, end);
        zones[i] = zone;
    }

    FastLED.addLeds<NEOPIXEL, LEDS_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(DEFAULT_BRIGHTNESS);

    // Clear all LEDs
    leds.fill_solid(CRGB::Black);
    FastLED.show();
}
