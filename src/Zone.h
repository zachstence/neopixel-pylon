#pragma once

#include "FastLED.h"

#include "Direction.h"
#include "Patterns/Pattern.h"
#include "patterns.h"

class Zone {
public:
    CRGBSet leds;

    Zone(CRGBSet leds, Palette* palette, PatternFactory factory, Direction direction = Direction::Forward) : leds(leds), palette(palette), direction(direction) {
        this->setPattern(factory);
    }

    void setPalette(Palette* palette) {
        this->palette = palette;
        this->pattern->setPalette(palette);
    }

    void setPattern(PatternFactory factory) {
        if (this->pattern != nullptr) {
            delete this->pattern;
        }
        this->pattern = factory(this->leds, this->palette);
    }

    void clear() {
        this->leds.fill_solid(CRGB::Black);
    }

    void run() {
        this->pattern->run();
    }

private:
    Palette* palette;
    Pattern* pattern = nullptr;
    Direction direction;
};
