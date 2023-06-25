#pragma once

#include "Patterns/SolidColor.h"
#include "Patterns/Strobe.h"
#include "Patterns/Twinkle.h"
#include "Patterns/Off.h"

typedef Pattern* (*PatternFactory)(CRGBSet leds, Palette* palette);

const int NUM_PATTERNS = 3;

PatternFactory PATTERN_FACTORIES[NUM_PATTERNS] = {
    [](CRGBSet leds, Palette* palette) -> Pattern* {
        Serial.println("PatternFactory 0");
        auto pattern = new SolidColor(leds, palette);
        Serial.println("PatternFactory 0 done");
        return pattern;
    },
    // [](CRGBSet leds, Palette* palette) -> Pattern* {
    //     return new Strobe(leds, palette, Strobe::Opts { bpm: 300 });
    // },
    // [](CRGBSet leds, Palette* palette) -> Pattern* {
    //     return new Strobe(leds, palette, Strobe::Opts { bpm: 600 });
    // },
    // [](CRGBSet leds, Palette* palette) -> Pattern* {
    //     return new Strobe(leds, palette, Strobe::Opts { bpm: 1200 });
    // },
    [](CRGBSet leds, Palette* palette) -> Pattern* {
        return new Twinkle(leds, palette);
    },
    [](CRGBSet leds, Palette* palette) -> Pattern* {
        return new Off(leds, palette);
    },
};
