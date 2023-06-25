#include "FastLED.h"

#include "Pattern.h"

class Off : public Pattern {
public:
    struct Opts {
        CRGBSet leds;
    };

    Off(CRGBSet leds, Palette* palette): Pattern(leds, palette) {}

    void run() {
        this->leds = CRGB::Black;
        FastLED.show();
    }
};
