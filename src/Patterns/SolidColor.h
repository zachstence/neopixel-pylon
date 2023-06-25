#include "FastLED.h"

#include "Pattern.h"

class SolidColor : public Pattern {
public:
    SolidColor(CRGBSet leds, Palette* palette) : Pattern(leds, palette) {}

    void run() override {
        this->leds.fill_solid(*this->color());
        FastLED.show();
    }
};
