#include "FastLED.h"

#include "src/leds.h"
#include "src/patterns.h"
#include "src/palettes.h"

uint8_t patternIndex = 0;
Pattern* currentPattern;

uint8_t paletteIndex = 0;
Palette* currentPalette;

void cyclePattern() {
    patternIndex = (patternIndex + 1) % NUM_PATTERNS;
    delete currentPattern;
    currentPattern = PATTERN_FACTORIES[patternIndex](leds, currentPalette);
    currentPattern->setPalette(currentPalette);
}

void cyclePalette() {
    paletteIndex = (paletteIndex + 1) % NUM_PALETTES;
    currentPalette = PALETTES[paletteIndex];
    currentPattern->setPalette(currentPalette);
}


////////////////////


void setup() {
    setupLeds();

    currentPalette = PALETTES[paletteIndex];
    currentPattern = PATTERN_FACTORIES[patternIndex](leds, currentPalette);
}

void loop() {
    EVERY_N_SECONDS(2) {
        cyclePalette();
        cyclePattern();
    }

    currentPattern->run();
}
