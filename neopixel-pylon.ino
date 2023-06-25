#include "FastLED.h"

#include "src/Pylon.h"

Pylon* pylon;

void setup() {
    pylon = new Pylon();
}

void loop() {
    EVERY_N_SECONDS(2) {
        pylon->cyclePalette();
        pylon->cyclePattern();
    }

    pylon->run();
}
