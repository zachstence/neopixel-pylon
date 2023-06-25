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
        this->testLeds();

        auto palette = PALETTES[0];
        auto pattern = PATTERN_FACTORIES[0];

        // Split LEDs into zones
        for (int i = 0; i < NUM_ZONES; i++) {
            int start = i * LEDS_PER_ZONE;
            int end = start + LEDS_PER_ZONE - 1;
            auto direction = (i % 2 == 0) ? Direction::Forward : Direction::Backward;
            Zone* zone = new Zone(CRGBSet(this->leds, start, end), palette, pattern, direction);
            zones[i] = zone;
        }

        this->clear();
        this->runStartupAnimation();
    }

    void testLeds() {
        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CRGB::Black;
        }
        FastLED.show();
        delay(500);
        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CRGB::Red;
        }
        FastLED.show();
        delay(500);
        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CRGB::Green;
        }
        FastLED.show();
        delay(500);
        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CRGB::Blue;
        }
        FastLED.show();
        delay(500);
    }

    void runStartupAnimation() {
        for (int i = 0; i < LEDS_PER_ZONE; i++) {
            for (int z = 0; z < NUM_ZONES; z++) {
                this->zones[z]->leds[i] = CRGB::White;
            }
            FastLED.show();
            delay(50);
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
        auto nextPatternMod = p % NUM_PATTERNS;
        this->patternIndex = nextPatternMod;
        auto pattern = PATTERN_FACTORIES[this->patternIndex];

        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->setPattern(pattern);
        }
    }

    void cyclePalette() {
        this->setPalette(this->paletteIndex + 1);
    }

    void cyclePattern() {
        auto nextPattern = this->patternIndex + 1;
        this->setPattern(nextPattern);
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
