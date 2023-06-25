#pragma once

#include "FastLED.h"

#include "Direction.h"
#include "Patterns/Pattern.h"
#include "patterns.h"

class Zone {
public:
    CRGBSet leds;

    Zone(CRGBSet leds, Palette* palette, PatternFactory factory, Direction direction = Direction::Forward) : leds(leds), palette(palette), direction(direction) {
        Serial.println("Zone()");
        Serial.print("  Palette h");
        Serial.println(palette[0]->h);
        delay(100);
        this->setPattern(factory);
        Serial.println("Zone() done");
        delay(100);
    }

    void setPalette(Palette* palette) {
        Serial.println("Zone.setPalette()");
        this->palette = palette;
        this->pattern->setPalette(palette);
        Serial.println("Zone.setPalette() done");
    }

    void setPattern(PatternFactory factory) {
        Serial.println("Zone.setPattern()");
        delay(100);
        if (this->pattern != nullptr) {
            Serial.println("Deleting previous pattern");
            delay(100);
            delete this->pattern;
            Serial.println("  done");
            delay(100);
        }
        Serial.println("Instantiating new pattern");
        delay(100);
        this->pattern = factory(this->leds, this->palette);
        Serial.println("  done");
        delay(100);
        Serial.println("Zone.setPattern() done");
        delay(100);
    }

    void clear() {
        Serial.println("Zone.clear()");
        this->leds.fill_solid(CRGB::Black);
        Serial.println("Zone.clear() done");
    }

    void run() {
        EVERY_N_MILLIS(500) {
            Serial.println("Zone.run()");
        }
        this->pattern->run();
        EVERY_N_MILLIS(500) {
            Serial.println("Zone.run() done");
        }
    }

private:
    Palette* palette;
    Pattern* pattern = nullptr;
    Direction direction;
};
