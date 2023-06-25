#pragma once

#include "FastLED.h"

#include "config.h"
#include "palettes.h"
#include "patterns.h"
#include "Zone.h"

class Pylon {
public:
    Pylon() {
        // Setup LEDs
        FastLED.addLeds<NEOPIXEL, LEDS_PIN>(this->leds, NUM_LEDS);
        FastLED.setBrightness(DEFAULT_BRIGHTNESS_PERCENT * 255 / 100);

        this->clear();

        auto palette = PALETTES[0];
        auto pattern = PATTERN_FACTORIES[0];

        this->leds[0] = CRGB::Green;
        FastLED.show();

        // Split LEDs into zones
        for (int i = 0; i < NUM_ZONES; i++) {
            int start = i * LEDS_PER_ZONE;
            int end = start + LEDS_PER_ZONE - 1;
            Zone* zone = new Zone(CRGBSet(this->leds, start, end), palette, pattern);
            zones[i] = zone;
        }
    }

    void setPalette(int p) {
        this->paletteIndex = p % NUM_PALETTES;
        auto palette = PALETTES[this->paletteIndex];

        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->setPalette(palette);
        }
    }

    void setPattern(int p) {
        this->patternIndex = p % NUM_PATTERNS;
        auto pattern = PATTERN_FACTORIES[p];

        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->setPattern(pattern);
        }
    }

    void cyclePalette() {
        this->setPalette(this->paletteIndex + 1);
    }

    void cyclePattern() {
        this->setPattern(this->patternIndex + 1);
    }

    void clear() {
        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->clear();
        }
        FastLED.show();
    }

    void run() {
        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->run();
        }
    }

private:
    CRGB leds[NUM_LEDS];
    Zone* zones[NUM_ZONES];

    int paletteIndex = 0;
    int patternIndex = 0;
};
