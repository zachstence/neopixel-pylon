#pragma once

#include "FastLED.h"

#include "../palettes.h"

class Pattern {
public:
    virtual void run() = 0;

    void setPalette(Palette* palette) {
        this->palette = palette;
    }

    CHSV color(uint8_t index) {
        // TODO support palettes with multiple colors
        return *this->palette[index];
    }

protected:
    Palette* palette;
};
