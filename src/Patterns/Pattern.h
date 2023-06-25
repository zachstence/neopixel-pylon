#pragma once

#include "FastLED.h"

#include "../palettes.h"
#include "../Direction.h"

class Pattern {
public:
    Pattern(CRGBSet leds, Palette* palette, Direction direction = Direction::Forward) :
        leds(leds),
        palette(palette),
        direction(direction)
    {}

    virtual ~Pattern() {}

    virtual void run() = 0;

    void setPalette(Palette* palette) {
        this->palette = palette;
    }

    CHSV* color() {
        return this->palette[0];
    }

protected:
    CRGBSet leds;
    Palette* palette;
    Direction direction;
};
