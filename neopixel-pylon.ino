#include "FastLED.h"

#include "src/Pylon.h"

Pylon* pylon;

void setup() {
    Serial.println("setup()");
    delay(4000);
    pylon = new Pylon();
    Serial.println("setup() done");
    delay(100);
}

void loop() {
    EVERY_N_MILLIS(500) {
        Serial.println("loop()");
    }

    EVERY_N_SECONDS(2) {
        pylon->cyclePalette();
        pylon->cyclePattern();
    }

    Serial.println("loop()");
    delay(100);
    pylon->run();
}
