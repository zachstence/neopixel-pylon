#pragma once

#include "FastLED.h"

#include "config.h"
#include "palettes.h"
#include "patterns.h"
#include "Zone.h"

class Pylon {
public:
    Pylon() {
        Serial.println("Pylon()");
        delay(100);
        // Setup LEDs
        FastLED.addLeds<NEOPIXEL, LEDS_PIN>(this->leds, NUM_LEDS);
        FastLED.setBrightness(DEFAULT_BRIGHTNESS_PERCENT * 255 / 100);

        Serial.println("Testing RGB");
        delay(100);

        for (int i = 0; i < NUM_LEDS; i++) {
            this->leds[i] = CRGB::Black;
        }
        delay(500);
        FastLED.show();
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

        Serial.println("Getting default palette and pattern");
        delay(100);

        auto palette = PALETTES[0];
        auto pattern = PATTERN_FACTORIES[0];

        Serial.println("Setting up zones");
        delay(100);

        // Split LEDs into zones
        for (int i = 0; i < NUM_ZONES; i++) {
            int start = i * LEDS_PER_ZONE;
            int end = start + LEDS_PER_ZONE - 1;
            Serial.print("  Zone ");
            Serial.print(start);
            Serial.print(" ");
            Serial.print(end);
            Serial.print(" ");
            Serial.println();
            Zone* zone = new Zone(CRGBSet(this->leds, start, end), palette, pattern);
            zones[i] = zone;
        }

        Serial.println("Setting up zones done");
        delay(100);

        this->clear();
        this->runStartupAnimation();

        Serial.println("Pylon() done");
        delay(100);
    }

    void runStartupAnimation() {
        Serial.println("Pylon.runStartupAnimation()");
        for (int i = 0; i < LEDS_PER_ZONE; i++) {
            for (int z = 0; z < NUM_ZONES; z++) {
                this->zones[z]->leds[i] = CRGB::White;
            }
            FastLED.show();
            delay(50);
        }
        Serial.println("Pylon.runStartupAnimation() done");
    }

    void setPalette(int p) {
        Serial.print("Pylon.setPalette() ");
        Serial.println(p);
        this->paletteIndex = p % NUM_PALETTES;
        Serial.println(this->paletteIndex);
        auto palette = PALETTES[this->paletteIndex];

        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->setPalette(palette);
        }
        Serial.println("Pylon.setPalette() done");
    }

    void setPattern(int p) {
        Serial.print("Pylon.setPattern() ");
        Serial.print(p);
        Serial.print(" ");
        auto nextPatternMod = p % NUM_PATTERNS;
        Serial.print(nextPatternMod);
        Serial.println();
        this->patternIndex = nextPatternMod;
        Serial.println(this->patternIndex);
        auto pattern = PATTERN_FACTORIES[this->patternIndex];

        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->setPattern(pattern);
        }
        Serial.println("Pylon.setPattern() done");
    }

    void cyclePalette() {
        Serial.println("Pylon.cyclePalette()");
        this->setPalette(this->paletteIndex + 1);
        Serial.println("Pylon.cyclePalette() done");
    }

    void cyclePattern() {
        Serial.print("Pylon.cyclePattern() -> ");
        auto nextPattern = this->patternIndex + 1;
        Serial.print(nextPattern);
        Serial.println();
        this->setPattern(nextPattern);
        Serial.println("Pylon.cyclePattern() done");
    }

    void clear() {
        Serial.println("Pylon.clear()");
        for (int i = 0; i < NUM_ZONES; i++) {
            this->zones[i]->clear();
        }
        FastLED.show();
        Serial.println("Pylon.clear() done");
    }

    void run() {
        EVERY_N_MILLIS(500) {
            Serial.print("run ");
            Serial.print(this->paletteIndex);
            Serial.print(" ");
            Serial.print(this->patternIndex);
            Serial.println();
        }
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
